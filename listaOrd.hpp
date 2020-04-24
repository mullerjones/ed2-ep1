#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "util.hpp"
using namespace std;

class listaOrd
{
public:
    NoLista* iniLista;
    listaOrd(string nomeArquivo);
    ~listaOrd();
    void insere(String chave, Integer valor);
    Integer devolve(String chave);
    void remove(String chave);
    int rank(String chave);
    String seleciona(int k);
};