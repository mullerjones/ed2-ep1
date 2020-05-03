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
        delete aux2->valor;
        delete aux2;
        aux2 = nullptr;
    }
}

void listaDes::insere(String chave, Integer valor)
{
    NoLista *aux = new NoLista();
    aux->chave = (String)malloc(40 * sizeof(char) + 5);
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
    delete aux->valor;
    delete aux;
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