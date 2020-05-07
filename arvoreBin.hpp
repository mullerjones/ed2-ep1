#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "util.hpp"
using namespace std;

void libera(NoABB *raiz);
void liberaNo(NoABB *no);
NoABB *coloca(NoABB *novo, NoABB *raiz);
int contaFilhos(NoABB *raiz);

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

arvoreBin::~arvoreBin()
{
    libera(raiz);
}

void arvoreBin::insere(String chave, Integer valor)
{
    NoABB *novo = new NoABB();
    novo->chave = (String)malloc(40 * sizeof(char));
    strcpy(novo->chave, chave);
    novo->valor = valor;
    novo->esq = nullptr;
    novo->dir = nullptr;

    raiz = coloca(novo, raiz);
}

Integer arvoreBin::devolve(String chave)
{
    if (raiz == nullptr)
        return nullptr;
    NoABB *aux = raiz;
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

void arvoreBin::remove(String chave)
{
    NoABB *p = raiz;
    int valor = strcasecmp(p->chave, chave);
    while (p != nullptr && valor != 0)
    {
        if (valor > 0)
        {
            p = p->esq;
        }
        else
        {
            p = p->dir;
        }
        valor = strcasecmp(p->chave, chave);
    }
    NoABB *praSair = p;
    NoABB *q = nullptr;
    p = nullptr;

    if (praSair->esq == nullptr)
    {
        q = praSair->dir;
        liberaNo(praSair);
        return;
    }
    p = praSair;
    q = praSair->esq;
    while (q->dir != nullptr)
    {
        p = q;
        q = q->dir;
    }
    if (strcasecmp(p->chave, chave))
    {
        p->dir = q->esq;
        q->esq = praSair->esq;
    }
    q->dir = praSair->dir;
    liberaNo(praSair);
}

int arvoreBin::rank(String chave)
{
    int rank = 0;
    NoABB *aux = raiz;
    while (aux != nullptr && !strcasecmp(aux->chave, chave))
    {
        if (strcasecmp(aux->chave, chave) > 0)
        {
            aux = aux->esq;
        }
        else
        {
            rank += contaFilhos(aux->esq);
            aux = aux->dir;
        }
    }
    rank += contaFilhos(aux->esq);
    return rank - 1; //Subtrai 1 do valor obtido ate aqui ja que nao se deve contar a si mesmo
}

String arvoreBin::seleciona(int k)
{
    NoABB *auxNo = raiz;
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

NoABB *coloca(NoABB *novo, NoABB *raiz)
{
    if (raiz == nullptr)
        return novo;
    int valor = strcasecmp(novo->chave, raiz->chave);
    if (valor > 0)
        raiz->esq = coloca(novo, raiz->esq);
    else
        raiz->dir = coloca(novo, raiz->dir);
    return raiz;
}

void liberaNo(NoABB *no)
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

void libera(NoABB *raiz)
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

int contaFilhos(NoABB *raiz)
{
    if (raiz == nullptr)
        return 0;
    int total = 1;
    total += contaFilhos(raiz->dir);
    total += contaFilhos(raiz->esq);
    return total;
}