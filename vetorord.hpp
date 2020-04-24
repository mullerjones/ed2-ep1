#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "util.hpp"
using namespace std;

bool comparador(Valor a, Valor b)
{
    return strcasecmp(a.chave, b.chave) < 0;
}

class vetorOrd
{
public:
    vector<Valor> vetor;
    vetorOrd(string nomeArquivo);
    ~vetorOrd();
    void insere(String chave, Integer valor);
    Integer devolve(String chave);
    void remove(String chave);
    int rank(String chave);
    String seleciona(int k);
private:
    int find(String chave, int ini, int fin);
    int achaLugar(String chave);
};

vetorOrd::vetorOrd(string nomeArquivo)
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

vetorOrd::~vetorOrd()
{
    for (std::size_t i = 0; i < vetor.size(); ++i)
    {
        free(vetor[i].chave);
        free(vetor[i].valor);
    }
}

void vetorOrd::insere(String chave, Integer valor)
{
    Valor aux;
    aux.chave = (String)malloc(20 * sizeof(char));
    strcpy(aux.chave, chave);
    aux.valor = valor;
    if(vetor.size()==0)
    {
        vetor.push_back(aux);
    }
    else
    {
        vetor.push_back(aux);
        sort(vetor.begin(), vetor.end(), &comparador);
        //int index = achaLugar(chave);
        //vetor.insert(vetor.begin()+index+1, aux);
    }
    return;
}

Integer vetorOrd::devolve(String chave)
{
    int index = find(chave, 0, vetor.size()-1);
    if(index == -1) return nullptr;
    return vetor[index].valor;
}

void vetorOrd::remove(String chave)
{
    int index = find(chave, 0, vetor.size()-1);
    free(vetor[index].valor);
    free(vetor[index].chave);
    vetor.erase(vetor.begin() + index);
}

int vetorOrd::rank(String chave)
{
    int rank = find(chave, 0, vetor.size()-1);
    return rank;
}

String vetorOrd::seleciona(int k)
{
    return vetor[k].chave;
}

int vetorOrd::find(String chave, int ini, int fin)
{
    if(vetor.size() == 0) return -1;
    int i = (ini+fin)/2;
    int valor = strcasecmp(vetor[i].chave, chave);
    if(ini == fin && valor != 0)
    {
        return -1;
    }

    if (valor == 0) return i;

    switch (valor/abs(valor))
    {
        case -1:
            return find(chave, i+1, fin);
        case 1:
            return find(chave, ini, i);
    }
}

int vetorOrd::achaLugar(String chave)
{
    int ini = 0;
    int fin = vetor.size()-1;
    if(ini == fin)
    {
        int num = strcasecmp(chave, vetor[0].chave);
        if(num > 0) return 1;
        else return 0;
    }
    int lugar = (ini + fin)/2;
    while(vetor[lugar+1].chave < chave || vetor[lugar].chave > chave)
    {
        if(vetor[lugar].chave > chave)
        {
            ini = lugar;
            lugar = (ini+fin)/2 + 1;
        }
        else
        {
            fin = lugar;
            lugar = (ini+fin)/2;
        }
    }
    return lugar;

}