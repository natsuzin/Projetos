// QUICKSORT

#ifndef QUICKSORT_H_INCLUDED
#define QUICKSORT_H_INCLUDED
#include "functions.h"
#include <iostream>

using namespace std;

int partition(int arr[], int low, int high, int &c, int &t)
{
    int pivot = arr[high];

    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
            contaTrocas(t);
        }
        contaComparacoes(c);
        contaComparacoes(c);
    }
    swap(arr[i + 1], arr[high]);
    contaTrocas(t);

    return (i + 1);
}

void quickSort(int arr[], int low, int high, int &c, int &t)
{
    if (low < high)
    {
        int pi = partition(arr, low, high, c, t);
        quickSort(arr, low, pi - 1, c, t);
        quickSort(arr, pi + 1, high, c, t);
    }
    contaComparacoes(c);
}

void mostraQ(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        cout << "[" << arr[i] << "]";
    cout << "\n";
}

#endif // QUICKSORT_H_INCLUDED
