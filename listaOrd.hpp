#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "util.hpp"
using namespace std;

bool comparador(NoLista* a, NoLista* b)
{
    return strcasecmp(a->chave, b->chave) < 0;
}

class listaOrd
{
public:
    NoLista *iniLista;
    listaOrd(string nomeArquivo);
    ~listaOrd();
    void insere(String chave, Integer valor);
    Integer devolve(String chave);
    void remove(String chave);
    int rank(String chave);
    String seleciona(int k);
};

listaOrd::listaOrd(string nomeArquivo)
{
    ifstream arqTexto;
    string palavra;
    String test = (String) malloc(40*sizeof(char) + 5);
    Integer aux = nullptr;
    iniLista = nullptr;
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

listaOrd::~listaOrd()
{
    NoLista *aux = nullptr;
    NoLista *aux2 = nullptr;
    aux = iniLista;
    iniLista = nullptr;
    while (aux != nullptr)
    {
        aux2 = aux;
        aux = aux->prox;
        free(aux2->chave);
        delete aux2->valor;
        delete aux2;
        aux2 = nullptr;
    }
}

void listaOrd::insere(String chave, Integer valor)
{
    NoLista *novo = new NoLista();
    novo->chave = (String)malloc(40 * sizeof(char));
    strcpy(novo->chave, chave);
    novo->valor = valor;
    novo->prox = nullptr;

    NoLista *aux = nullptr;
    NoLista *aux2 = nullptr;
    aux = iniLista;
    while (aux != nullptr && comparador(aux,novo))
    {
        aux2 = aux;
        aux = aux->prox;
    }
    if (aux == nullptr)
    {
        if (aux2 == nullptr)
        {
            novo->prox = iniLista;
            iniLista = novo;
        }
        else
        {
            aux2->prox = novo;
        }
    }
    else
    {
        if (aux2 == nullptr)
        {
            if(iniLista == aux) iniLista = novo;
            novo->prox = aux->prox;
            aux->prox = novo;
        }
        else
        {
            aux2->prox = novo;
            novo->prox = aux;
        }
    }
}

Integer listaOrd::devolve(String chave)
{
    NoLista *aux = iniLista;
    while (aux != nullptr && strcasecmp(aux->chave, chave))
    {
        aux = aux->prox;
    }
    if (aux != nullptr)
        return aux->valor;
    else
        return nullptr;
}

void listaOrd::remove(String chave)
{
    NoLista *aux;
    NoLista *aux2;
    aux = iniLista;
    while (aux != nullptr && !strcasecmp(aux->chave, chave))
    {
        aux2 = aux;
        aux = aux->prox;
    }
    aux2->prox = aux->prox;
    free(aux->chave);
    delete aux->valor;
    delete aux;
    aux = nullptr;
}

int listaOrd::rank(String chave)
{
    int rank = 0;
    NoLista *aux = iniLista;
    while (aux != nullptr && strcasecmp(aux->chave, chave))
    {
        rank++;
    }
    if (aux == nullptr)
        return -1;

    return rank;
}

String listaOrd::seleciona(int k)
{
    int count = 0;
    NoLista *aux = iniLista;
    while (aux != nullptr && count < k)
    {
        aux = aux->prox;
        count++;
    }
    if (aux == nullptr)
        return nullptr;
    return aux->chave;
}