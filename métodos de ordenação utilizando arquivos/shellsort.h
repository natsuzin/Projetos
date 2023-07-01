// SHELLSORT

#ifndef SHELLSORT_H_INCLUDED
#define SHELLSORT_H_INCLUDED
#include "functions.h"
#include <iostream>

using namespace std;

void shellSort(int arr[], int n, int &c, int &t)
{
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i ++)
        {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
            {
                arr[j] = arr[j - gap];
                contaTrocas(t);
                contaComparacoes(c);
            }
            arr[j] = temp;
            contaTrocas(t);
            contaComparacoes(c);
        }
    }
}

void mostraS(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        cout << "[" << arr[i] << "]";
    cout << "\n";
}

#endif // SHELLSORT_H_INCLUDED
