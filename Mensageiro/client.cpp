#include <iostream>
#include "client.h"
#include <fstream>
#include <cstdio>

using namespace std;

bool Client::cadastrado (void) const {
  ifstream arq;
  arq.open("cadastrados.txt");
  string l, s, dado, lixo;
  if (!arq.is_open()){
    cerr << "erro na leitura de cadastrados.txt" << endl;
    return false;
  }
  while (arq >> dado){
    if (dado == "login:"){
      arq >> l;
      arq >> lixo >> s;
      if (l==login){
        arq.close();
        if(s==senha) return true;
        return false;
      }
    }
  }
  arq.close();
  return false;
}

bool Client::cadastrar (void) const{
  ofstream arq;
  arq.open("cadastrados.txt",ios::app);
  int dado;
  if (!arq.is_open()){
    cerr << "erro na leitura de cadastrados.txt" << endl;
    return false;
  }
  arq << "login: " << login << endl << "senha: " << senha << endl;
  arq.close();
  return true;
}

bool Client::existente (void) const {
  ifstream arq;
  arq.open("cadastrados.txt");
  string l, dado;
  if (!arq.is_open()){
    cerr << "erro na leitura de cadastrados.txt" << endl;
    return false;
  }
  while (arq >> dado){
    if (dado == "login:"){
      arq >> l;
      if (l==login){
        arq.close();
        return true;
      }
    }
  }
  arq.close();
  return false;
}
