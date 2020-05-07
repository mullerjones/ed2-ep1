#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "util.hpp"
using namespace std;

void libera(NoRN *raiz);
void liberaNo(NoRN *no);

class arvoreRN
{
public:
    NoRN* raiz;
    arvoreRN(string nomeArquivo);
    void insere(String chave, Integer valor);
    Integer devolve(String chave);
    void remove(String chave);
    int rank(String chave);
    String seleciona(int k);
};

arvoreRN::arvoreRN(string nomeArquivo)
{
    ifstream arqTexto;
    string palavra;
    String test = (String) malloc(40*sizeof(char) + 5);
    Integer aux = nullptr;
    raiz = nullptr;
    arqTexto.open(nomeArquivo);
    while (arqTexto >> palavra)
    {
        strcpy(test, palavra.c_str());
        aux = devolve(test);
        if (aux == nullptr)
        {
            int *um = new int;
            *um = 1;
            insere(test, um);
        }
        else
        {
            (*aux)++;
        }
    }
    free(test);
    test = nullptr;
    aux = nullptr;
    arqTexto.close();
}






String arvoreRN::seleciona(int k)
{
    NoRN *auxNo = raiz;
    int auxRank = 0;
    int acum = 0;
    while (auxNo != nullptr)
    {
        auxRank = rank(auxNo->chave);
        if (auxRank > k)
        {
            auxNo = auxNo->esq;
        }
        else if (auxRank == k)
        {
            return auxNo->chave;
        }
        else
        {
            auxNo = auxNo->dir;
        }
    }
    return nullptr;
}

////////////////////////
void liberaNo(NoRN *no)
{
    delete no->valor;
    free(no->chave);
    no->chave = nullptr;
    no->valor = nullptr;
    no->esq = nullptr;
    no->dir = nullptr;
    delete no;
    no = nullptr;
    return;
}

void libera(NoRN *raiz)
{
    if (raiz->esq != nullptr)
    {
        libera(raiz->esq);
        raiz->esq = nullptr;
    }
    if (raiz->dir != nullptr)
    {
        libera(raiz->dir);
        raiz->dir = nullptr;
    }
    if (raiz->dir == nullptr && raiz->esq == nullptr)
    {
        liberaNo(raiz);
        raiz = nullptr;
    }
    else
    {
        ERROR(chegou na hora de liberar a raiz e nao tava tudo nullptr);
    }
    return;
}