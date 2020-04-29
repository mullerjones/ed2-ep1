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
    String palavra;
    Integer aux = nullptr;
    vetor.reserve(100000);
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

vetorDes::~vetorDes()
{
    for (std::size_t i = 0; i < vetor.size(); ++i)
    {
        free(vetor[i].chave);
        free(vetor[i].valor);
    }
}

void vetorDes::insere(String chave, Integer valor)
{
    Valor aux;
    aux.chave = (String)malloc(20 * sizeof(char));
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

void vetorDes::remove(String chave)
{
    for (std::size_t i = 0; i < vetor.size(); ++i)
    {
        if (!strcasecmp(vetor[i].chave, chave))
        {
            vetor.erase(vetor.begin() + i - 1);
        }
    }
}

int vetorDes::rank(String chave)
{
    int total = 0;
    for (std::size_t i = 0; i < vetor.size(); ++i)
    {
        if (vetor[i].chave < chave)
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
        aux = rank(vetor[i].chave);
        if(aux == 0) return vetor[i].chave;
    }
    return nullptr;
}