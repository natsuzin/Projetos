#ifndef CONTADOR_H_INCLUDED
#define CONTADOR_H_INCLUDED
#include <iostream>

using namespace std;

void zeraContadores(int &comparacoes, int &trocas)
{
    comparacoes = 0;
    trocas = 0;
}

void contaComparacoes(int &comparacoes)
{
    comparacoes++;
}

void mostraComparacoes(int comparacoes)
{
    cout << comparacoes;
}

void contaTrocas(int &trocas)
{
    trocas++;
}

void mostraTrocas(int trocas)
{
    cout << trocas;
}

float valorRelativo(float valorAtual, float valorMaximo)
{
    return (valorAtual / valorMaximo) * 100;
}

float achaMaior(float heapSort, float mergeSort, float quickSort, float shellSort)
{

    if(heapSort > mergeSort && heapSort > quickSort && heapSort > shellSort)
    {
        return heapSort;
    }
    else
    {
        if(mergeSort > quickSort && mergeSort > shellSort)
        {
            return mergeSort;
        }
        else
        {
            if(quickSort > heapSort && quickSort > shellSort)
            {
                return quickSort;
            }
            else
            {
                return shellSort;
            }
        }
    }
}

void gravaNoArquivo(ofstream &arqResultados, int quantidade, float comp, float troca, int i)
{
    if(i==1)
        arqResultados << "heapSort            " << quantidade << "                    ";
    if(i==2)
        arqResultados << "mergeSort           " << quantidade << "                    ";
    if(i==3)
        arqResultados << "quickSort           " << quantidade << "                    ";
    if(i==4)
        arqResultados << "shellSort           " << quantidade << "                    ";
    arqResultados << fixed << setprecision(2) << comp << "                 ";
    arqResultados << fixed << setprecision(2) << troca;
    arqResultados << endl;
}

#endif // CONTADOR_H_INCLUDED
