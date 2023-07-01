// HEAPSORT

#ifndef HEAPSORT_H_INCLUDED
#define HEAPSORT_H_INCLUDED
#include "functions.h"
#include <iostream>

using namespace std;

void heapify(int arr[], int n, int i, int &c, int &t)
{
    int largest = i, cont = 0;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;
    if (r < n && arr[r] > arr[largest])
        largest = r;

    while(cont<4)
    {
        contaComparacoes(c);
        cont++;
    }

    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        contaTrocas(t);
        heapify(arr, n, largest, c, t);
    }
    contaComparacoes(c);
}

void heapSort(int arr[], int n, int &c, int &t)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, c, t);

    for (int i = n - 1; i >= 0; i--)
    {
        swap(arr[0], arr[i]);
        contaTrocas(t);
        heapify(arr, i, 0, c, t);
    }
}

void mostraH(int arr[], int n)
{
    for (int i = 0; i < n; ++i)
        cout << "[" << arr[i] << "]";
    cout << "\n";
}

#endif // HEAPSORT_H_INCLUDED
