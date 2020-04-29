#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "util.hpp"
using namespace std;

void libera(NoTreap* raiz);
void liberaNo(NoTreap* no);
NoTreap* coloca(NoTreap *novo, NoTreap *raiz);

class treap
{
public:
    NoTreap* raiz;
    treap(string nomeArquivo);
    ~treap();
    void insere(String chave, Integer valor);
    Integer devolve(String chave);
    void remove(String chave);
    int rank(String chave);
    String seleciona(int k);
};

treap::treap(string nomeArquivo)
{
    ifstream arqTexto;
    String palavra;
    Integer aux = nullptr;
    raiz = nullptr;
    arqTexto.open(nomeArquivo);
    while (arqTexto >> palavra)
    {
        aux = devolve(palavra);
        if (aux == nullptr)
        {
            int *um = new int;
            *um = 1;
            insere(palavra, um);
        }
        else
        {
            (*aux)++;
        }
    }
    arqTexto.close();
    delete (palavra);
    palavra = nullptr;
    aux = nullptr;

}
treap::~treap()
{

}
void treap::insere(String chave, Integer valor)
{

}
Integer treap::devolve(String chave)
{

}
void treap::remove(String chave)
{

}
int treap::rank(String chave)
{

}
String treap::seleciona(int k)
{

}