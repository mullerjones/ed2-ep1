#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "util.hpp"
using namespace std;

class listaDes
{
public:
    NoLista *iniLista;
    listaDes(string nomeArquivo);
    ~listaDes();
    void insere(String chave, Integer valor);
    Integer devolve(String chave);
    void remove(String chave);
    int rank(String chave);
    String seleciona(int k);
};

listaDes::listaDes(string nomeArquivo)
{
    ifstream arqTexto;
    String palavra;
    Integer aux = nullptr;
    iniLista = nullptr;
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

listaDes::~listaDes()
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
        free(aux2->valor);
        free(aux2);
        aux2 = nullptr;
    }
}

void listaDes::insere(String chave, Integer valor)
{
    NoLista *aux = new NoLista();
    aux->chave = (String)malloc(20 * sizeof(char));
    strcpy(aux->chave, chave);
    aux->valor = valor;
    aux->prox = iniLista;
    iniLista = aux;
}

Integer listaDes::devolve(String chave)
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

void listaDes::remove(String chave)
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
    free(aux->valor);
    free(aux);
    aux = nullptr;
}

int listaDes::rank(String chave)
{
    NoLista* aux;
    int total = 0;
    aux = iniLista;
    while(aux!= nullptr)
    {
        if(aux->chave < chave) total++;
        aux = aux->prox;
    }
    return total;
}

String listaDes::seleciona(int k)
{
    NoLista* aux = iniLista;
    while(aux!=nullptr && rank(aux->chave) != k)
    {
        aux = aux->prox;
    }
    return aux->chave;
}