#include <string>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "util.hpp"
using namespace std;

void libera(NoTreap *raiz);
void liberaNo(NoTreap *no);
NoTreap *coloca(NoTreap *novo, NoTreap *raiz);
NoTreap *rotDir(NoTreap *raiz);
NoTreap *rotEsq(NoTreap *raiz);
int contaFilhosT(NoTreap *raiz);

class treap
{
public:
    NoTreap *raiz;
    int seed;
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
    string palavra;
    String test = (String) malloc(40*sizeof(char) + 5);
    Integer aux = nullptr;
    raiz = nullptr;
    seed = 5;
    srand(seed);
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

treap::~treap()
{
    libera(raiz);
}

void treap::insere(String chave, Integer valor)
{
    NoTreap *novo = new NoTreap();
    novo->chave = (String)malloc(20 * sizeof(char));
    strcpy(novo->chave, chave);
    novo->valor = valor;
    novo->esq = nullptr;
    novo->dir = nullptr;
    novo->pai = nullptr;
    novo->prior = rand() % 10000;

    if(raiz == nullptr)
    {
        raiz = novo;
        return;
    }
    else
    {
        NoTreap* aux = raiz;
        int achou = 0;
        int valor = strcasecmp(chave, raiz->chave);
        while(!achou)
        {
            if(valor > 0)
            {
                //vai pra esquerda
            }
        }
    }
}

Integer treap::devolve(String chave)
{
    if (raiz == nullptr)
        return nullptr;
    NoTreap *aux = raiz;
    int valor = strcasecmp(aux->chave, chave);
    while (aux != nullptr && valor != 0)
    {
        if (valor > 0)
        {
            aux = aux->esq;
        }
        else
        {
            aux = aux->dir;
        }
        if (aux != nullptr)
            valor = strcasecmp(aux->chave, chave);
    }
    if (aux == nullptr)
        return nullptr;
    else
        return aux->valor;
}

void treap::remove(String chave)
{
}

int treap::rank(String chave)
{
    int rank = 0;
    NoTreap *aux = raiz;
    while (aux != nullptr && !strcasecmp(aux->chave, chave))
    {
        if (strcasecmp(aux->chave, chave) > 0)
        {
            aux = aux->esq;
        }
        else
        {
            rank += contaFilhosT(aux->esq);
            aux = aux->dir;
        }
    }
    rank += contaFilhosT(aux->esq);
    return rank - 1;
}

String treap::seleciona(int k)
{
}

void libera(NoTreap *raiz)
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

void liberaNo(NoTreap *no)
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

NoTreap *rotDir(NoTreap *raiz)
{
    NoTreap *aux = raiz->esq;
    raiz->esq = aux->dir;
    aux->dir = raiz;
    return aux;
}

NoTreap *rotEsq(NoTreap *raiz)
{
    NoTreap *aux = raiz->dir;
    raiz->dir = aux->esq;
    aux->esq = raiz;
    return aux;
}

NoTreap *coloca(NoTreap *novo, NoTreap *raiz)
{
    if (raiz == nullptr)
        return novo;
    NoTreap* aux = nullptr;
    int valor = strcasecmp(novo->chave, raiz->chave);
    if (valor > 0)
        raiz->esq = coloca(novo, raiz->esq);
    else
        raiz->dir = coloca(novo, raiz->dir);

    if (raiz->esq->prior > raiz->prior)
        raiz = rotDir(raiz);
    else if (raiz->dir->prior > raiz->prior)
        raiz = rotEsq(raiz);

    return raiz;
}

int contaFilhosT(NoTreap *raiz)
{
    if (raiz == nullptr)
        return 0;
    int total = 1;
    total += contaFilhosT(raiz->dir);
    total += contaFilhosT(raiz->esq);
    return total;
}