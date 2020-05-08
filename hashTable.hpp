#include <string>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>

#include "util.hpp"
using namespace std;

int meuHash(String chave);

class hashTable
{
public:
    map<int, NoLista> tabela;
    hashTable(string nomeArquivo);
    ~hashTable();
    void insere(String chave, Integer valor);
    Integer devolve(String chave);
    void remove(String chave);
    int rank(String chave);
    String seleciona(int k);
};

hashTable::hashTable(string nomeArquivo)
{
    ifstream arqTexto;
    String palavra;
    Integer aux = nullptr;
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

hashTable::~hashTable()
{
    NoLista* aux;
    NoLista* aux2;
    for(auto it = tabela.begin(); it != tabela.end(); it++)
    {
        aux = &it->second;
        while(aux != nullptr)
        {
            aux2 = aux;
            aux = aux->prox;
            free(aux2->chave);
            delete aux2->valor;
            delete aux2;
            aux2 = nullptr;
        }
    }
}

void hashTable::insere(String chave, Integer valor)
{
    NoLista *novo = new NoLista();
    novo->chave = (String)malloc(20 * sizeof(char));
    strcpy(novo->chave, chave);
    novo->valor = valor;
    novo->prox = nullptr;

    int novoHash = meuHash(chave);
    if (tabela.find(novoHash) == tabela.end())
    {
        NoLista* cab = new NoLista();
        cab->chave = nullptr;
        cab->valor = nullptr;
        cab->prox = nullptr;
        tabela.insert(pair<int, NoLista>(novoHash, *cab));
        cab->prox = novo;
    }
    else
    {
        NoLista *aux;
        aux = &tabela[novoHash];
        while (aux->prox != nullptr)
            aux = aux->prox;
        aux->prox = novo;
    }
}

Integer hashTable::devolve(String chave)
{
    int hashDesse = meuHash(chave);
    if (tabela.find(hashDesse) != tabela.end())
        return tabela[hashDesse].valor;
    else
        return nullptr;
}

void hashTable::remove(String chave)
{
}

int hashTable::rank(String chave)
{
}

String hashTable::seleciona(int k)
{
}

int meuHash(String chave)
{
    int saida = 0;
    for (char c = chave[0]; c != '\0'; c++)
    {
        saida += (int)c;
    }
    saida = saida % 256;
    return saida;
}