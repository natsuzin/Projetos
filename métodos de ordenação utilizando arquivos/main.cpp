#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>
#include "heapsort.h"
#include "shellsort.h"
#include "mergesort.h"
#include "quicksort.h"
#include "functions.h"
#define TMAX 10000

using namespace std;

int main()
{
    string nomeArquivo;
    int dados[TMAX], opcao, opcao2, quantidade, c, t;

    ofstream ofsArq("dados.txt");

    ifstream ifsArq;

    cout << "Informe o nome do arquivo: ";
    getline(cin, nomeArquivo);

    ifsArq.open(nomeArquivo, ios::in); // aqui tenta abrir o arquivo com o nome que o usuario digitou.

    system("cls");

    if(!ifsArq)
        cout << "Arquivo '" << nomeArquivo << "' nao pode ser aberto. Tente novamente";

    else
    {
        ofstream arqResultados("Resultados.txt");
        arqResultados << "Nome       |     Quantidade      |     Comparacoes     |        Trocas" << endl; // aqui colocamos a base do arquivo de resultados
        do
        {
            for (int i = 0; i < TMAX; i++)
                dados[i] = rand(); // Gera um número aleatório e o armazena no array
            heapSort(dados, TMAX, c, t);
            for (int i = 0; i < TMAX; i++)
                ofsArq << dados[i] << "\n"; // Armazena-os em um arquivo dados.txt

            cout << "-----------Menu-----------\n"
                 "Informe a opcao desejada:\n"
                 " 1 - Realizar simulacao\n"
                 " 2 - Sair\n"
                 "--------------------------\n"
                 "Opcao: ";
            cin >> opcao;
            cin.ignore();
            system("cls");

            switch (opcao)
            {
            case 1:
            {
                do
                {
                    cout << "Informe a quantidade de dados a serem ordenados (1 a 10.000): " << endl;
                    cin >> quantidade;
                    system("cls");
                    if (quantidade < 1 || quantidade > 10000)
                    {
                        cout << "Quantidade incorreta. Tente novamente.\n";
                        system("pause");
                        system("cls");
                    }
                }
                while (quantidade < 1 || quantidade > 10000);

                do
                {
                    cout << "Informe a ordem inicial: \n";
                    cout << "1 - Crescente\n";
                    cout << "2 - Decrescente\n";
                    cout << "3 - Aleatoria\n";
                    cin >> opcao2;
                    if (opcao2 < 1 || opcao2 > 3)
                    {
                        cout << "Quantidade incorreta. Tente novamente.\n";
                        system("pause");
                        system("cls");
                    }
                }
                while(opcao2 < 1 || opcao2 > 3);

                switch (opcao2)
                {
                case 1:
                    heapSort(dados, quantidade, c, t);
                    break;

                case 2:
                    for(int i=quantidade/2 -1; i>=0; i--)
                        heapify(dados,quantidade,i,c,t);
                    break;

                case 3:
                    for (int i = 0; i < quantidade; i++)
                        dados[i] = rand();
                }

                system("cls");

                float compMax, trocaMax;

                // aqui estamos fazendo a conta dos maiores para definir o valor de 100 % para o maior;

                zeraContadores(c, t);
                heapSort(dados, quantidade, c, t);
                float compHeap = c;
                float trocaHeap = t;

                zeraContadores(c, t);
                mergeSort(dados, 0, quantidade - 1, c, t);
                float compMerge = c;
                float trocaMerge = t;

                zeraContadores(c, t);
                quickSort(dados, 0, quantidade - 1, c, t);
                float compQuick = c;
                float trocaQuick = t;

                zeraContadores(c, t);
                shellSort(dados, quantidade, c, t);
                float compShell = c;
                float trocaShell = t;

                compMax = achaMaior(compHeap, compMerge, compQuick, compShell);
                trocaMax = achaMaior(trocaHeap, trocaMerge, trocaQuick, trocaShell);

                compHeap = valorRelativo(compHeap, compMax);
                compMerge = valorRelativo(compMerge, compMax);
                compQuick = valorRelativo(compQuick, compMax);
                compShell = valorRelativo(compShell, compMax);

                trocaHeap = valorRelativo(trocaHeap, trocaMax);
                trocaMerge = valorRelativo(trocaMerge, trocaMax);
                trocaQuick = valorRelativo(trocaQuick, trocaMax);
                trocaShell = valorRelativo(trocaShell, trocaMax);

                arqResultados << endl;
                gravaNoArquivo(arqResultados, quantidade, compHeap, trocaHeap, 1);
                gravaNoArquivo(arqResultados, quantidade, compMerge, trocaMerge, 2);
                gravaNoArquivo(arqResultados, quantidade, compQuick, trocaQuick, 3);
                gravaNoArquivo(arqResultados, quantidade, compShell, trocaShell, 4);
                arqResultados << endl;

                cout << "Dados gravados no arquivo com sucesso!\n";
                break;
            }

            case 2:
                arqResultados.close();
                cout << "Saindo...\n";
                break;
            }

            if (opcao < 1 || opcao > 2)
                cout << "Opcao inexistente. Tente novamente.\n";
            system("pause");
            system("cls");
        }
        while (opcao != 2);
    }

    ifsArq.close();

    return 0;
}
