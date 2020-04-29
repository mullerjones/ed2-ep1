#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "util.hpp"
using namespace std;

void libera(NoABB* raiz);
void liberaNo(NoABB* no);
NoABB* coloca(NoABB *novo, NoABB *raiz);

class arvoreBin
{
public:
    NoABB *raiz;
    arvoreBin(string nomeArquivo);
    ~arvoreBin();
    void insere(String chave, Integer valor);
    Integer devolve(String chave);
    void remove(String chave);
    int rank(String chave);
    String seleciona(int k);
};

arvoreBin::arvoreBin(string nomeArquivo)
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

arvoreBin::~arvoreBin()
{
    libera(raiz);
}

void arvoreBin::insere(String chave, Integer valor)
{
    NoABB* novo = new NoABB();
    novo->chave = (String) malloc(20*sizeof(char));
    strcpy(novo->chave, chave);
    novo->valor = valor;
    novo->esq = nullptr;
    novo->dir = nullptr;

    raiz = coloca(novo, raiz);
}

Integer arvoreBin::devolve(String chave)
{
    if(raiz == nullptr) return nullptr;
    NoABB* aux = raiz;
    int valor = strcasecmp(aux->chave, chave);
    while(aux != nullptr && valor != 0)
    {
        if(valor > 0)
        {
            aux = aux->esq;
        }
        else
        {
            aux = aux->dir;
        }
        if(aux!=nullptr) valor =  strcasecmp(aux->chave, chave);
    }
    if(aux == nullptr) return nullptr;
    else return aux->valor;
}

void arvoreBin::remove(String chave)
{
    NoABB* p = raiz;
    int valor = strcasecmp(p->chave, chave);
    while(p != nullptr && valor != 0)
    {
        if(valor > 0)
        {
            p = p->esq;
        }
        else
        {
            p = p->dir;
        }
        valor =  strcasecmp(p->chave, chave);
    }
    NoABB* praSair = p;
    NoABB* q = nullptr;
    p = nullptr;

    if(praSair->esq == nullptr)
    {
        q = praSair->dir;
        liberaNo(praSair);
        return;
    }
    p = praSair;
    q = praSair->esq;
    while(q->dir!=nullptr)
    {
        p = q;
        q = q->dir;
    }
    if(strcasecmp(p->chave, chave))
    {
        p->dir = q->esq;
        q->esq = praSair->esq;
    }
    q->dir = praSair->dir;
    liberaNo(praSair);
}

int arvoreBin::rank(String chave)
{
    return 0;
}

String arvoreBin::seleciona(int k)
{
    return nullptr;
}

NoABB* coloca(NoABB *novo, NoABB *raiz)
{
    if(raiz == nullptr) return novo;
    int valor = strcasecmp(novo->chave, raiz->chave);
    if(valor > 0) raiz->esq = coloca(novo, raiz->esq);
    else raiz->dir = coloca(novo, raiz->dir);
    return raiz;
}

void liberaNo(NoABB* no)
{
    free(no->valor);
    free(no->chave);
    no->chave = nullptr;
    no->valor = nullptr;
    no->esq = nullptr;
    no->dir = nullptr;
    free(no);
    no = nullptr;
    return;
}

void libera(NoABB* raiz)
{
    if(raiz->esq != nullptr) libera(raiz->esq);
    
    if(raiz->dir != nullptr) libera(raiz->dir);

    if(raiz->dir == nullptr && raiz->esq == nullptr) liberaNo(raiz);
    else
    {
        ERROR(chegou na hora de liberar a raiz e nao tava tudo nullptr);
    }
    return;
}