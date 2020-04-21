#include <string>
#include <iostream>
#include <fstream>

/*
pra montar a tabela:
1- abre arquivo
2- pra cada palavra:
    ve se ta na tabela
        se nao, adiciona
        se sim, incrementa
    

*/

//Vetor desordenado
template <typename Chave, typename Item>
class vetorDes
{
    template <typename Chave, typename Item> class vetorDes(string nomeArquivo)
    {
        fstream arqTexto;
        arqTexto.open(nomeArquivo);
    }
    void insere(Chave chave, Item valor)
    {

    }
    Item devolve(Chave chave);
    void remove(Chave chave);
    int rank(Chave chave);
    Chave seleciona(int k);
};
//Vetor ordenado
template <typename Chave, typename Item>
class vetorOrd
{
    void insere(Chave chave, Item valor);
    Item devolve(Chave chave);
    void remove(Chave chave);
    int rank(Chave chave);
    Chave seleciona(int k);
};
//Lista ligada desordenada
template <typename Chave, typename Item>
class listaDes
{
    void insere(Chave chave, Item valor);
    Item devolve(Chave chave);
    void remove(Chave chave);
    int rank(Chave chave);
    Chave seleciona(int k);
};
//Lista ligada ordenada
template <typename Chave, typename Item>
class listaOrd
{
    void insere(Chave chave, Item valor);
    Item devolve(Chave chave);
    void remove(Chave chave);
    int rank(Chave chave);
    Chave seleciona(int k);
};
//Árvore Binária
template <typename Chave, typename Item>
class arvoreBin
{
    void insere(Chave chave, Item valor);
    Item devolve(Chave chave);
    void remove(Chave chave);
    int rank(Chave chave);
    Chave seleciona(int k);
};
//Treaps
template <typename Chave, typename Item>
class treap
{
    void insere(Chave chave, Item valor);
    Item devolve(Chave chave);
    void remove(Chave chave);
    int rank(Chave chave);
    Chave seleciona(int k);
};

//Árvore 2-3
template <typename Chave, typename Item>
class arvore23
{
    void insere(Chave chave, Item valor);
    Item devolve(Chave chave);
    void remove(Chave chave);
    int rank(Chave chave);
    Chave seleciona(int k);
};
//Árvore Rubro-Negra
template <typename Chave, typename Item>
class arvoreRN
{
    void insere(Chave chave, Item valor);
    Item devolve(Chave chave);
    void remove(Chave chave);
    int rank(Chave chave);
    Chave seleciona(int k);
};
//Hashing Table
template <typename Chave, typename Item>
class hashTable
{
    void insere(Chave chave, Item valor);
    Item devolve(Chave chave);
    void remove(Chave chave);
    int rank(Chave chave);
    Chave seleciona(int k);
};

/*
void insere (Chave, chave, Item valor);
Item devolve (Chave chave);
void remove (Chave chave);
int rank (Chave chave);
Chave seleciona(int k);




*/
