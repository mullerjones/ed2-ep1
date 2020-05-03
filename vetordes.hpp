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
    string palavra;
    String test = (String)malloc(40 * sizeof(char) + 5);
    Integer aux = nullptr;
    vetor.reserve(100000);
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

vetorDes::~vetorDes()
{
    for (std::size_t i = 0; i < vetor.size(); ++i)
    {
        free(vetor[i].chave);
        delete vetor[i].valor;
    }
    vetor.clear();
}

void vetorDes::insere(String chave, Integer valor)
{
    Valor aux;
    aux.chave = (String)malloc(40 * sizeof(char) + 5);
    strcpy(aux.chave, chave);
    aux.valor = valor;
    vetor.push_back(aux);
    return;
}

Integer vetorDes::devolve(String chave)
{
    for (std::size_t i = 0; i < vetor.size(); ++i)
    {
        String teste = vetor.at(i).chave;
        if (!strcasecmp(teste, chave))
        {
            return vetor.at(i).valor;
        }
    }
    return nullptr;
}

void vetorDes::remove(String chave)
{
    for (std::size_t i = 0; i < vetor.size(); ++i)
    {
        if (!strcasecmp(vetor.at(i).chave, chave))
        {
            free(vetor.at(i).chave);
            delete vetor.at(i).valor;
            vetor.erase(vetor.begin() + i - 1);
        }
    }
}

int vetorDes::rank(String chave)
{
    int total = 0;
    if(devolve(chave) == nullptr) return -1;
    for (std::size_t i = 0; i < vetor.size(); ++i)
    {
        if (strcasecmp(vetor.at(i).chave, chave) < 0)
        {
            total++;
        }
    }

    return total;
}

String vetorDes::seleciona(int k)
{
    int aux = -1;
    for (std::size_t i = 0; i < vetor.size(); ++i)
    {
        aux = rank(vetor.at(i).chave);
        if (aux == k)
            return vetor.at(i).chave;
    }
    return nullptr;
}