#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string.h>
#include <time.h>

#include "vetordes.hpp"
#include "vetorord.hpp"
#include "listaDes.hpp"
#include "util.hpp"
#include "tabeladesimbolos.hpp"
using namespace std;

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
        cout<<st->vetor[10].chave << endl;
        cout<<*(st->vetor[10].valor) << endl;

        delete st;
    }
    else if (tipo == "VO"){
        start = clock(); 
        vetorOrd *st = new vetorOrd(nome_arquivo);
        end = clock();

        /* calcule o tempo */
        elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << "arquivo lido e ST construida em " << elapsed << " segundos\n";

		delete st;
    }
    else if (tipo == "LD"){
        start = clock(); 
        listaDes *st = new listaDes(nome_arquivo);
        end = clock();

        /* calcule o tempo */
        elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << "arquivo lido e ST construida em " << elapsed << " segundos\n";

		delete st;
    }

    return 0;
}