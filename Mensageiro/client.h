#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <iostream>
#include <string>
#include "winsocket.h"
#include "mensageiro.h"

using namespace std;

// Classe que armazena os dados que definem um cliente: login e socket
class Client
{
private:
  string login;
  string senha;
public:
  tcp_winsocket s;
  inline Client(): login(""), senha(""), s() {}
  inline Client(string l): login(l.c_str()), senha(""), s() {}
  inline Client(string l, string se, tcp_winsocket tcp) {login=l.c_str(); senha=se.c_str(); s=tcp;}
  inline bool operator==(const string &L) {return login==L;}
  bool cadastrado (void) const;
  bool cadastrar (void) const;
  bool existente (void) const;

  inline string getLogin(void) const {return login;}
};

#endif
