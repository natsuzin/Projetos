#ifndef CALCULADORA_H_INCLUDED
#define CALCULADORA_H_INCLUDED

#include <iostream>
#include "Pilha.h"

using namespace std;

template <typename T>
void inicia(Pilha<T> &pilha)
{
    cria(pilha);
}

template <typename T>
void zera(Pilha<T> &pilha)
{
    int contador = pilha.cardinalidade;
    while(contador > 1){
        retira(pilha);
        contador--;
    }
}

template <typename T>
T soma(T elemento, T elementoAnterior)
{
    return elementoAnterior + elemento;
}

template <typename T>
T subtrai(T elemento, T elementoAnterior)
{
    return elementoAnterior - elemento;
}

template <typename T>
T multiplica(T elemento, T elementoAnterior)
{
    return elementoAnterior * elemento;
}

template <typename T>
T divide(T elemento, T elementoAnterior)
{
    return elementoAnterior / elemento;
}

template <typename T>
void parcelas(Pilha<T> pilha)
{
    Nodo<T> *q = pilha.fim;
    int contador = 0;
    if(pilha.cardinalidade > 2){
        while(contador != 2)
        {
            q = q->anterior;
            contador++;
        }
        for (Nodo<T>* p = q; p != NULL; p = p->anterior)
            cout << "[" << p->elemento << "]";
    }
    cout << endl;
}

template<typename T>
T igual(Pilha<T> pilha)
{
    T elemento = topo(pilha);
    return elemento;
}

template <typename T>
void fim(Pilha<T> &pilha)
{
    destroi(pilha);
}


#endif // CALCULADORA_H_INCLUDED
