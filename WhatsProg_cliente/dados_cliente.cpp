#include "dados_cliente.h"

bool Conversa::setUsuario(const string &U)
{
    if (U.size()<TAM_MIN_NOME_USUARIO || U.size()>TAM_MAX_NOME_USUARIO)
    {
        correspondente = "";
        return false;
    }
    correspondente = U;
    return true;
}

Mensagem &Conversa::operator[](unsigned i)
{
    static Mensagem vazia;
    return (i<size() ? LM[i] : vazia);
}

unsigned Conversa::getNumMsgsEntregues() const
{
    unsigned numMsgsEntregues=0;
    for (unsigned i=0; i<LM.size(); i++)
    {
        if (LM[i].getRemetente()==correspondente &&
            LM[i].getStatus()==MSG_ENTREGUE)
        {
            numMsgsEntregues++;
        }
    }
    return numMsgsEntregues;
}


DadosCliente::DadosCliente():
    servidor(""),meuUsuario(""),idConversa(-1),idMensagem(0),LC()
{
}

void DadosCliente::clearServidorUsuario()
{
    servidor = "";
    meuUsuario = "";
    setIdConversa(-1);
    clearConversas();
}

bool DadosCliente::setServidorUsuario(const string &IP, const string &MU)
{
    // Sempre que altera a conexao, apaga todas as conversas
    setIdConversa(-1);
    clearConversas();

    if (IP=="" || MU.size()<TAM_MIN_NOME_USUARIO || MU.size()>TAM_MAX_NOME_USUARIO)
    {
        servidor = "";
        meuUsuario = "";
        return false;
    }
    servidor = IP;
    meuUsuario = MU;
    return true;
}

bool DadosCliente::setIdConversa(int ID)
{
    if (ID >= (int)size())
    {
        idConversa = -1;
        return false;
    }
    idConversa = ID;
    return true;
}

Conversa &DadosCliente::operator[](unsigned i)
{
    static Conversa vazia;
    return (i<size() ? LC[i] : vazia);
}

// Cria nova conversa com o nome do usuario passado como parametro
bool DadosCliente::insertConversa(const string &U)
{
    Conversa C;
    if (!C.setUsuario(U)) return false; // Erro na atribuicao do nome da conversa
    LC.push_back(C);
    //emit conversasModificada();
    return true;
}

bool DadosCliente::eraseConversa(unsigned i)
{
    if (i >= size())
    {
        return false;
    }
    LC.erase(LC.begin()+i);
    return true;
}

void DadosCliente::setMsgStatus(int32_t id, MsgStatus st) {
    for (unsigned int i=0; i<LC.size(); i++) {
        for (unsigned int j=0; j<LC[i].size(); j++) {
            if (LC[i][j].getRemetente()==meuUsuario && LC[i][j].getId() == id) {
                LC[i][j].setStatus(st);
                /*if(st==MSG_ENTREGUE){
                    LC[i].getNumMsgsEntregues();
                }*/
            }
        }
    }
}

void DadosCliente::attMsg(int conversaIndex, int32_t id, const string &r) {
    for (unsigned int i=0; i<LC[conversaIndex].size(); i++) {
        if (LC[conversaIndex][i].getRemetente()!=meuUsuario && LC[conversaIndex][i].getId() == id) {
             LC[conversaIndex][i].setRemetente(r);
        }
    }
}
void DadosCliente::salvarDados(void) const {
    return;
}
