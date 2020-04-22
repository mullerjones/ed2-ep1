#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "util.hpp"
using namespace std;

struct Valor
{
    String chave;
    Integer valor;
};

/*
pra montar a tabela:
1- abre arquivo
2- pra cada palavra:
    ve se ta na tabela
        se nao, adiciona
        se sim, incrementa
    

*/

//Vetor desordenado
class vetorDes
{
public:
    vector<Valor> vetor;
    vetorDes(string nomeArquivo);
    ~vetorDes();
    void insere(String chave, Integer valor);
    Integer devolve(String chave);
    void remove(String chave);
    int rank(String chave);
    String seleciona(int k);
};

vetorDes::vetorDes(string nomeArquivo)
{
    ifstream arqTexto;
    String palavra;
    Integer aux = nullptr;
    vetor.reserve(100000);
    arqTexto.open(nomeArquivo);
    while (arqTexto >> palavra)
    {
        aux = devolve(palavra);
        if (aux == nullptr)
        {
            int* um = new int;
            *um = 1;
            insere(palavra, um);
        }
        else
        {
            (*aux)++;
        }
    }
    free(palavra);
}

void vetorDes::insere(String chave, Integer valor)
{
    Valor aux;
    aux.chave = (String) malloc(20*sizeof(char));
    strcpy(aux.chave, chave);
    aux.valor = valor;
    vetor.push_back(aux);
    return;
}

Integer vetorDes::devolve(String chave)
{
    for (std::size_t i = 0; i < vetor.size(); ++i)
    {
        String teste = vetor[i].chave;
        if (!strcasecmp(teste, chave))
        {
            return vetor[i].valor;
        }
    }
    return nullptr;
}

vetorDes::~vetorDes()
{
    for (std::size_t i = 0; i < vetor.size(); ++i)
    {
        free(vetor[i].chave);
        free(vetor[i].valor);
    }
}

//Vetor ordenado
class vetorOrd
{
public:
    vetorOrd(string nomeArquivo);
    void insere(String chave, Integer valor);
    Integer devolve(String chave);
    void remove(String chave);
    int rank(String chave);
    String seleciona(int k);
};

vetorOrd::vetorOrd(string nomeArquivo)
{
    cout<<"teste"<<endl;
}

//Lista ligada desordenada
class listaDes
{
public:
    listaDes(string nomeArquivo);
    void insere(String chave, Integer valor);
    Integer devolve(String chave);
    void remove(String chave);
    int rank(String chave);
    String seleciona(int k);
};
//Lista ligada ordenada
class listaOrd
{
public:
    listaOrd(string nomeArquivo);
    void insere(String chave, Integer valor);
    Integer devolve(String chave);
    void remove(String chave);
    int rank(String chave);
    String seleciona(int k);
};
//Árvore Binária
class arvoreBin
{
public:
    arvoreBin(string nomeArquivo);
    void insere(String chave, Integer valor);
    Integer devolve(String chave);
    void remove(String chave);
    int rank(String chave);
    String seleciona(int k);
};
//Treaps
class treap
{
public:
    treap(string nomeArquivo);
    void insere(String chave, Integer valor);
    Integer devolve(String chave);
    void remove(String chave);
    int rank(String chave);
    String seleciona(int k);
};

//Árvore 2-3
class arvore23
{
public:
    arvore23(string nomeArquivo);
    void insere(String chave, Integer valor);
    Integer devolve(String chave);
    void remove(String chave);
    int rank(String chave);
    String seleciona(int k);
};
//Árvore Rubro-Negra
class arvoreRN
{
public:
    arvoreRN(string nomeArquivo);
    void insere(String chave, Integer valor);
    Integer devolve(String chave);
    void remove(String chave);
    int rank(String chave);
    String seleciona(int k);
};
//Hashing Table
class hashTable
{
public:
    hashTable(string nomeArquivo);
    void insere(String chave, Integer valor);
    Integer devolve(String chave);
    void remove(String chave);
    int rank(String chave);
    String seleciona(int k);
};

/*
void insere (Chave, chave, Item valor);
Item devolve (Chave chave);
void remove (Chave chave);
int rank (Chave chave);
Chave seleciona(int k);

valgrind --leak-check=full ./unit_test2 [arquivo] [modo]


*/
