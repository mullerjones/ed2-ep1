#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string.h>
#include <time.h>
#include "util.hpp"

#include "vetordes.hpp"
#include "vetorord.hpp"
#include "listaDes.hpp"
#include "listaOrd.hpp"
#include "arvoreBin.hpp"
#include "treap.hpp"
#include "arvore23.hpp"
#include "arvoreRN.hpp"
#include "hashTable.hpp"

using namespace std;

#define PROMPT cout << ">>> ";
#define MIN_ST "minST"
#define DELMIN_ST "delminST"
#define GET_ST "getST"
#define RANK_ST "rankST"
#define DELETE_ST "deleteST"
#define SELECT_ST "selectST"

template <class ST>
void testeOperacoes(ST st);

int main(int argc, char *argv[])
{
    fstream arqTexto;

    /* abra arquivo com texto */
    arqTexto.open(argv[1]);

    if (arqTexto.fail())
    {
        cout << "ERRO: arquivo" << argv[1] << "nao pode ser aberto.\n";
        exit(EXIT_FAILURE);
    }

    arqTexto.close();

    string nome_arquivo = argv[1];
    string tipo = argv[2];

    /* crie a ST*/
    cout << "criando ST...\n";

    /* usadas para medir tempo de processamento */
    clock_t start, end;
    double elapsed = 0;

    if (tipo == "VD")
    {
        start = clock();
        vetorDes *st = new vetorDes(nome_arquivo);
        end = clock();

        /* calcule o tempo */
        elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
        cout << "arquivo lido e ST construida em " << elapsed << " segundos\n";
        cout << st->vetor[10].chave << endl;
        cout << *(st->vetor[10].valor) << endl;

        testeOperacoes(st);
        delete st;
    }
    else if (tipo == "VO")
    {
        start = clock();
        vetorOrd *st = new vetorOrd(nome_arquivo);
        end = clock();

        /* calcule o tempo */
        elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
        cout << "arquivo lido e ST construida em " << elapsed << " segundos\n";

        testeOperacoes(st);
        delete st;
    }
    else if (tipo == "LD")
    {
        start = clock();
        listaDes *st = new listaDes(nome_arquivo);
        end = clock();

        /* calcule o tempo */
        elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
        cout << "arquivo lido e ST construida em " << elapsed << " segundos\n";

        testeOperacoes(st);
        delete st;
    }
    else if (tipo == "LO")
    {
        start = clock();
        listaOrd *st = new listaOrd(nome_arquivo);
        end = clock();

        /* calcule o tempo */
        elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
        cout << "arquivo lido e ST construida em " << elapsed << " segundos\n";

        testeOperacoes(st);
        delete st;
    }
    else if (tipo == "AB")
    {
        start = clock();
        arvoreBin *st = new arvoreBin(nome_arquivo);
        end = clock();

        /* calcule o tempo */
        elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
        cout << "arquivo lido e ST construida em " << elapsed << " segundos\n";

        testeOperacoes(st);
        delete st;
    }
    else if (tipo == "TR"){
        start = clock(); 
        treap *st = new treap(nome_arquivo);
        end = clock();

        /* calcule o tempo */
        elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << "arquivo lido e ST construida em " << elapsed << " segundos\n";

        testeOperacoes(st);
		delete st;
     }
    // else if (tipo == "A23")
    // {
    //     start = clock();
    //     arvore23 *st = new arvore23(nome_arquivo);
    //     end = clock();

    //     /* calcule o tempo */
    //     elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
    //     cout << "arquivo lido e ST construida em " << elapsed << " segundos\n";

    //     testeOperacoes(st);
    //     delete st;
    // }
    // else if (tipo == "RN")
    // {
    //     start = clock();
    //     arvoreRN *st = new arvoreRN(nome_arquivo);
    //     end = clock();

    //     /* calcule o tempo */
    //     elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
    //     cout << "arquivo lido e ST construida em " << elapsed << " segundos\n";

    //     testeOperacoes(st);
    //     delete st;
    // }
    // else if (tipo == "HS")
    // {
    //     start = clock();
    //     hashTable *st = new hashTable(nome_arquivo);
    //     end = clock();

    //     /* calcule o tempo */
    //     elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
    //     cout << "arquivo lido e ST construida em " << elapsed << " segundos\n";

    //     testeOperacoes(st);
    //     delete st;
    // }
    else {
        cout << "A estrutura" << tipo << "não é válida";
        exit(EXIT_FAILURE);
    }

    return 0;
}

template <class ST>
void testeOperacoes(ST st)
{
    String linha = NULL;

    /* mostre uso */
    cout << "Possiveis operacoes do teste interativo:\n";
    cout << "minST, delminST, getST <chave>; rankST <chave>, deleteST <chave>, selectST <int>\n";
    cout << "CRTL-D para encerrar.\n";
    PROMPT;
    while ((linha = getLine(stdin)))
    {
        /* pegue operacao a ser testada */
        String operacao = getNextToken(linha);
        if (operacao == NULL)
        {
            ERROR(operacao esperada);
        }
        /*---------------------------------*/
        else if (!strcmp(operacao, MIN_ST))
        {
            String key = st->seleciona(0);
            if (key == NULL)
            {
                cout << "ST vazia\n";
            }
            else
            {
                cout << key << "\n";
            }
        }
        /*---------------------------------*/
        else if (!strcmp(operacao, DELMIN_ST))
        {
            String key = st->seleciona(0);
            if (key == NULL)
            {
                cout << "ST já está vazia\n";
            }
            else
            {
                cout << "\"" << key;
                st->remove(key);
                cout << "\" foi removida\n";
            }
        }
        /*---------------------------------*/
        else
        {
            /* operaÃ§Ã£o necessita de argumento key */
            String key = getNextToken(NULL);
            if (key == NULL)
            {
                ERROR(operacao necessita uma palavra);
            }
            else
            {
                /*---------------------------------*/
                if (!strcmp(operacao, GET_ST))
                {
                    Integer frequencia = NULL;
                    frequencia = st->devolve(key); /* consulte a ST */
                    /* mostre o resultado da consulta */
                    if (frequencia == NULL)
                    {
                        cout << key << ": 0\n";
                    }
                    else
                    {
                        cout << key << ": " << *frequencia << "\n";
                    }
                }
                /*---------------------------------*/
                else if (!strcmp(operacao, RANK_ST))
                {
                    int r = st->rank(key);
                    cout << r << "\n";
                }
                /*---------------------------------*/
                else if (!strcmp(operacao, DELETE_ST))
                {
                    st->remove(key);
                    cout << "\"" << key << "\" foi removida\n";
                }
                else if (!strcmp(operacao, SELECT_ST))
                {
                    int pos = atoi(key);
                    String chave = st->seleciona(pos);
                    cout << "Posição " << key << " = " << chave << "\n";
                }
                else
                {
                    ERROR(operacao nao reconhecida);
                }
            }
            free(key);
        }
        if (operacao != NULL)
            free(operacao);
        free(linha);
        PROMPT;
    }
    cout << "\n";
}
