// MERGESORT

#ifndef MERGESORT_H_INCLUDED
#define MERGESORT_H_INCLUDED
#include "functions.h"
#include <iostream>

using namespace std;

void merge(int arr[], int l, int m, int r, int &c, int &t)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int cont = 0;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
    {
        L[i] = arr[l + i];
        contaTrocas(t);
    }
    for (j = 0; j < n2; j++)
    {
        R[j] = arr[m + 1 + j];
        contaTrocas(t);
    }

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            contaTrocas(t);
            i++;
        }
        else
        {
            arr[k] = R[j];
            contaTrocas(t);
            j++;
        }
        contaComparacoes(c);
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        contaTrocas(t);
        i++;
        k++;
        contaComparacoes(c);
    }

    while (j < n2)
    {
        arr[k] = R[j];
        contaTrocas(t);
        j++;
        k++;
        contaComparacoes(c);
    }

    while (cont < 2)
    {
        contaComparacoes(c);
        cont++;
    }
}

void mergeSort(int arr[], int l, int r, int &c, int &t)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m, c, t);
        mergeSort(arr, m + 1, r, c, t);

        merge(arr, l, m, r, c, t);
    }
    contaComparacoes(c);
}

void mostraM(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        cout << "[" << arr[i] << "]";
    cout << "\n";
}

#endif // MERGESORT_H_INCLUDED
