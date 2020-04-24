#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "util.hpp"
using namespace std;

/*
pra montar a tabela:
1- abre arquivo
2- pra cada palavra:
    ve se ta na tabela
        se nao, adiciona
        se sim, incrementa
    

*/
//Vetor desordenado

//Vetor ordenado

//Lista ligada desordenada 

//Lista ligada ordenada

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
