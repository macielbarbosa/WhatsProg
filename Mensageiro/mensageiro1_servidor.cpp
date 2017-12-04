#include <iostream>
#include <string.h>
#include <list>
#include <algorithm>

#include "winsocket.h"
#include "mensageiro.h"
#include "client.h"

using namespace std;

/* ==================================================================

Este aplicativo cliente-servidor permite o envio de mensagens entre
os softwares clientes e o software servidor.
As mensagens trocadas sao formadas pelos seguintes campos:
1) Usuario - uma string formada por dois campos:
   1.1) Tamanho da string: um inteiro [ 4 bytes ]
   1.2) Caracteres da string: varios chars [ tamanho do texto ]
   Significa o destinatario, nas msgs do cliente para o servidor,
   ou o remetente, nas msgs do servidor para o cliente
2) Texto - uma string formada por dois campos:
   2.1) Tamanho do texto: um inteiro [ sizeof(int) bytes ]
   2.2) Caracteres do texto: varios chars [ tamanho do texto ]
   Contem a msg efetivamente enviada

A primeira msg a ser enviada pelo cliente para o servidor eh
diferente das demais. Deve conter apenas o nome do usuario. Esse
nome identificarah o cliente daih em diante: todas as msgs enviadas
para esse nome do usuario serao direcionadas pelo servidor para esse
cliente.

================================================================== */

enum
{
    CMD_NEW_USER=1001,
    CMD_LOGIN_USER=1002,
    CMD_LOGIN_OK=1003,
    CMD_LOGIN_INVALIDO=1004,
    CMD_NOVA_MSG=1005,
    CMD_MSG_RECEBIDA=1006,
    CMD_MSG_ENTREGUE=1007,
    CMD_MSG_LIDA1=1008,
    CMD_MSG_LIDA2=1009,
    CMD_ID_INVALIDA=1010,
    CMD_USER_INVALIDO=1011,
    CMD_MSG_INVALIDA=1012,
    CMD_LOGOUT_USER=1013,
    CMD_NOVA_CONVERSA=1014
} ComandoWhatsProg;

// Apelidos para uma lista de clientes e para o iterator correspondente
typedef list<Client> list_Client;
typedef list_Client::iterator iter_Client;

#define TEMPO_MAXIMO 60  // Tempo máximo de espera em segundos
#define TEMPO_ENVIO_LOGIN 60 // 60 segundos para o cliente enviar o nome de login apos conexao

//
// Variáveis globais das 2 threads
//
// O socket de conexoes
tcp_winsocket_server c;
// A lista de clientes
list_Client LC;
// O flag que indica que o software deve encerrar todas as threads
bool fim = false;

// Função auxiliar para enviar mensagem para um cliente especifico (dest)
// para o qual jah se tem um iterator que aponta para sua posicao dentro da
// lista de clientes
// Essa funcao deve ser chamada pela funcao envie_msg, que procurarah o
// destinatario especifico na lista e passarah o iterator
void envie_msg_um(const string &orig, iter_Client dest, const string &msg)
{
  WINSOCKET_STATUS iResult;

  // Escreve o login do remetente
  iResult = dest->s.write_string(orig);
  if ( iResult == SOCKET_ERROR )
  {
    cerr << "Problema na escrita do usuario no socket...\n";
    dest->s.shutdown();
  }
  if (dest->s.connected())
  {
    // Escreve o texto da msg
    iResult = dest->s.write_string(msg);
    if ( iResult == SOCKET_ERROR )
    {
      cerr << "Problema na escrita do texto no socket...\n";
      dest->s.shutdown();
    }
  }
}

// Funçoo auxiliar para enviar mensagem para um cliente especifico (dest != "ALL")
// ou para todos os clientes (dest == "ALL")
void envie_msg(const string &orig, const string &dest, const string &msg)
{
  iter_Client iDest;

  if (orig.size()<4 || orig.size()>16)
  {
    cerr << "Remetente (" << orig << ") invalido\n";
    return;
  }
  if (dest!="ALL" && (dest.size()<4 || dest.size()>16))
  {
    cerr << "Destinatario (" << dest << ") invalido\n";
    return;
  }
  if (dest=="ALL")
  {
    for (iDest=LC.begin(); iDest!=LC.end(); iDest++)
    {
      if (iDest->getLogin() != orig) envie_msg_um(orig, iDest, msg);
    }
  }
  else
  {
    // Procura o destinatario especificado dentro da lista de clientes
    iDest = find(LC.begin(), LC.end(), dest);
    if (iDest != LC.end())
    {
      envie_msg_um(orig, iDest, msg);
    }
    else
    {
      // O destinatario nao existe na lista atual de clientes
      cerr << "Usuario " << dest << " nao existe na lista de clientes\n";
    }
  }
}

// Thread que efetivamente desempenha as tarefas do servidor
DWORD WINAPI servidor(LPVOID lpParameter)
{
  tcp_winsocket t;
  winsocket_queue f;
  WINSOCKET_STATUS iResult;

  string usuario, senha, msg;
  iter_Client i;
  int32_t cmd;

  while (!fim)
  {
    // Inclui na fila de sockets para o select todos os sockets que eu
    // quero monitorar para ver se houve chegada de dados
    f.clean();
    if (!(fim = !c.accepting()))
    {
      f.include(c);
      for (i=LC.begin(); i!=LC.end(); i++)
      {
    	  if (i->s.connected())
    	  {
	        f.include(i->s);
    	  }
      }
    }
    // Espera que chegue alguma dados em qualquer dos sockets da fila
    iResult = f.wait_read(TEMPO_MAXIMO*1000);
    if (iResult==SOCKET_ERROR)
    {
      if (!fim) cerr << "Erro na espera por alguma atividade\n";
      fim = true;
    }
    if (!fim)
    {
      if (iResult!=0)
      {
        // Não saiu por timeout: houve atividade em algum socket da fila
        // Testa em qual socket houve atividade.

        // Primeiro, testa os sockets dos clientes
        for (i=LC.begin(); i!=LC.end(); i++)
        {
          if (i->s.connected() && f.had_activity(i->s))
          {
            iResult = i->s.read_int(cmd);
            if (iResult == SOCKET_ERROR)
            {
              cerr << "Erro socket do cliente " << i->getLogin() << ". Desconectando\n";
              LC.erase(i);
            }
            if (cmd == CMD_LOGOUT_USER) {
              cerr << "Usuario " << i->getLogin() << " deslogado." << endl;
              LC.erase(i);
              break;
            }
            if (cmd == CMD_NOVA_CONVERSA) {
              i->s.read_string(usuario);
              Client novo(usuario);
              cerr << "Usuario " << i->getLogin() << ": nova conversa com " << usuario <<endl;
              if(!novo.existente() ){
                i->s.write_int(CMD_USER_INVALIDO);
                cerr << "Usuario " << usuario << " nao existe." << endl;
                break;
              }
              i->s.write_int(CMD_NOVA_CONVERSA);
              cerr << "Conversa iniciada." << endl;
            }
            /*iResult = i->s.read_string(usuario);
            if (iResult == SOCKET_ERROR)
            {
              cerr << "Destinatario invalido (" << usuario << ") recebido do cliente " << i->login << ". Desconectando\n";
              i->s.shutdown();
            }
            if (i->s.connected())
            {
              iResult = i->s.read_string(msg);
              if (iResult == SOCKET_ERROR)
              {
                cerr << "Mensagem invalida recebida do cliente " << i->login << ". Desconectando\n";
                i->s.shutdown();
              }
            }
            if (i->s.connected())
            {
              cout << i->login << "->" << usuario << ": " << msg << endl;
              envie_msg(i->login,usuario,msg);
            }*/
          }
        }

        // Depois, esta se houve atividade no socket de conexao
        if (f.had_activity(c))
        {
          if (c.accept(t) != SOCKET_OK)
          {
            cerr << "Não foi possível estabelecer uma conexao\n";
            fim = true;
          }
          if (!fim)
          {
            // Leh o nome de usuario do cliente
            //iResult = t.read_string(usuario,TEMPO_ENVIO_LOGIN*1000);
            iResult = t.read_int(cmd);
            if (iResult == SOCKET_ERROR)
            {
              cerr << "Erro na leitura do comando.\n";
              t.close();
              continue;
            }
            iResult = t.read_string(usuario);
            if (iResult == SOCKET_ERROR)
            {
              cerr << "Erro na leitura do login.\n";
              t.close();
              continue;
            }
            iResult = t.read_string(senha);
            if (iResult == SOCKET_ERROR)
            {
              cerr << "Erro na leitura da senha.\n";
              t.close();
              continue;
            }
            if (usuario.size()<4 || usuario.size()>16)
            {
              cerr << "Nome de login (" << usuario << ") invalido.\n";
              t.close();
              continue;
            }
            if (senha.size()<4 || senha.size()>16)
            {
              cerr << "Nome de login (" << senha << ") invalido.\n";
              t.close();
              continue;
            }
            Client novo(usuario,senha,t);
            switch (cmd) {
              case (CMD_NEW_USER):
              {
                cout << "CMD_NEW_USER" << endl;
                if (novo.cadastrado()) {
                  cerr << "usuario " << usuario << "jah cadastrado" << endl;
                  t.write_int(CMD_LOGIN_INVALIDO);
                  t.close();
                  continue;
                }
                novo.cadastrar();
              }
              case (CMD_LOGIN_USER):
              {
                cout << "CMD_LOGIN_USER" << endl;
                if (!novo.cadastrado()) {
                  cerr << "Nome de login (" << usuario << ") nao cadastrado.\n";
                  t.write_int(CMD_LOGIN_INVALIDO);
                  t.close();
                  continue;
                }
                i = find(LC.begin(), LC.end(), usuario);
                if (i!= LC.end()) {
                  cerr << "Nome de login (" << usuario << ") jah utilizado.\n";
                  t.write_int(CMD_LOGIN_INVALIDO);
                  t.close();
                  continue;
                }
                LC.push_back(novo);
                cout << "Cliente " << usuario << " conectado.\n";
                t.write_int(CMD_LOGIN_OK);
              }
            }
          /*case (CMD_LOGIN_OK):
            cout << "CMD_LOGIN_OK";
            break;
          case (CMD_LOGIN_INVALIDO):
            cout << "CMD_LOGIN_INVALIDO";
            break;
          case (CMD_NOVA_MSG):
            cout << "CMD_NOVA_MSG";
            break;
          case (CMD_MSG_RECEBIDA):
            cout << "CMD_MSG_RECEBIDA";
            break;
          case (CMD_MSG_ENTREGUE):
            cout << "CMD_MSG_ENTREGUE";
            break;
          case (CMD_MSG_LIDA1):
            cout << "CMD_MSG_LIDA1";
            break;
          case (CMD_MSG_LIDA2):
            cout << "CMD_MSG_LIDA2";
            break;
          case (CMD_ID_INVALIDA):
            cout << "CMD_ID_INVALIDA";
            break;
          case (CMD_USER_INVALIDO):
            cout << "CMD_USER_INVALIDO";
            break;
          case (CMD_MSG_INVALIDA):
            cout << "CMD_MSG_INVALIDO";
            break;
          case (CMD_LOGOUT_USER):
            cout << "CMD_LOGOUT_USER";
            break;*/

          }
        }
      }
      else
      {
        // Saiu poe timeout: não houve atividade em nenhum socket da fila
        if (LC.empty())
        {
          cout << "Servidor inativo hah " << TEMPO_MAXIMO << " segundos...\n";
        }
      }

      // Depois de testar a chegada de dados em todos os sockets,
      // elimina da lista de sockets as conexoes que foram fechadas porque houve
      // falha na comunicacao ou porque se desligaram
      for (i=LC.begin(); i!=LC.end(); i++)
      {
        while ( i!=LC.end() && !(i->s.connected()) )
        {
          i->s.close();
          i = LC.erase(i);
        }
      }
    }
  }
  return 0;
}

int main(void)
{
  WSADATA wsaData;
  string msg;

  // All processes that call Winsock functions must first initialize the use of the Windows Sockets DLL (WSAStartup)
  // before making other Winsock functions calls
  // The MAKEWORD(2,2) parameter of WSAStartup makes a request for version 2.2 of Winsock on the system
  WINSOCKET_STATUS iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
  if (iResult != 0) {
    cerr << "WSAStartup failed: " << iResult << endl;
    exit(1);
  }

  if (c.listen(PORTA_TESTE) != SOCKET_OK) {
    cerr << "Não foi possível abrir o socket de controle\n";
    exit(1);
  }

  // Cria a thread que recebe e reenvia as mensagens
  HANDLE tHandle = CreateThread(NULL, 0, servidor, NULL , 0, NULL);
  if (tHandle == NULL)
  {
    cerr << "Problema na criação da thread: " << GetLastError() << endl;
    exit(1);
  }


  while (!fim)
  {
    do
    {
      cout << "Mensagem para todos os clientes [max " << TAM_MAX_MSG_STRING << " caracteres, FIM para terminar]: ";
      cin >> ws;
      getline(cin,msg);
    } while (msg.size()==0 || msg.size()>TAM_MAX_MSG_STRING);
    if (!fim) fim = (msg=="FIM");
    if (!fim)
    {
      envie_msg("SERVIDOR","ALL",msg);
    }
  }

  // Desliga os sockets
  cout << "Encerrando o socket de conexoes\n";
  c.shutdown();
  for (iter_Client i=LC.begin(); i!=LC.end(); i++)
  {
    cout << "Encerrando o socket do cliente " << i->getLogin() << endl;
    i->s.shutdown();
  }
  // Espera pelo fim da thread do servidor (máximo de 5 segundos)
  cout << "Aguardando o encerramento da outra thread...\n";
  WaitForSingleObject(tHandle, 5000);
  // Encerra na "força bruta" a thread do servidor caso ela não tenha terminado sozinha
  // (ou seja, a função WaitForSingleObject tenha saído por timeout)
  TerminateThread(tHandle,0);
  // Encerra o handle da thread
  CloseHandle(tHandle);
  // Enderra o socket
  c.close();
  for (iter_Client i=LC.begin(); i!=LC.end(); i++) i->s.close();

  /* call WSACleanup when done using the Winsock dll */
  WSACleanup();
}
