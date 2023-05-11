#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED

#include <iostream>

using namespace std;

template <typename T>
struct Nodo {
    T elemento;
    Nodo<T>* proximo;
    Nodo<T>* anterior;
};

template<typename T>
struct Pilha
{
    int cardinalidade;
    Nodo<T>* inicio;
    Nodo<T>* fim;
};

template<typename T>
void cria(Pilha<T> &pilha)
{
    pilha.cardinalidade = 0;
    pilha.inicio = NULL;
    pilha.fim = NULL;
}

template<typename T>
bool ehVazia(Pilha<T> pilha)
{
    return pilha.cardinalidade == 0;
}

template<typename T>
int numeroDeElementos(Pilha<T> pilha)
{
    return pilha.cardinalidade;
}

template<typename T>
bool existeElemento(Pilha<T> pilha, T elemento)
{
    Nodo<T> *p = pilha.inicio, *q = pilha.fim;
    while(p != NULL)
    {
        if(p->elemento == elemento || q->elemento == elemento)
            return true;
        p = p->proximo;
        q = q->anterior;
    }
    return false;
}

template<typename T>
bool validaPosicao(Pilha<T> pilha, int posicao)
{
    return (posicao >= 1) && (posicao <= pilha.cardinalidade);
}

template<typename T>
T topo(Pilha<T> pilha)
{
    return pilha.inicio->elemento;
}

template<typename T>
int recuperaPosicao(Pilha<T> pilha, T elemento)
{
    Nodo<T> *p = pilha.inicio, *q = pilha.fim;
    int contador = 1, contadorFim ;
    if(!existeElemento(pilha,elemento))
        throw "Elemento inexistente";
    while(p != NULL || q != NULL)
    {
        if(p->elemento == elemento)
            return contador;
        if(q->elemento == elemento)
            return contadorFim;
        p = p->proximo;
        q = q->anterior;
        contador++;
        contadorFim--;
    }
}

template<typename T>
void insere(Pilha<T> &pilha, T elemento)
{
    Nodo<T>* q = new Nodo<T>;
    q->elemento = elemento;
    q->proximo = NULL;
    q->anterior = NULL;
    if (pilha.inicio == NULL){
        pilha.inicio = q;
        pilha.fim = q;
    }
    else
    {
        Nodo<T>* p = pilha.inicio;
        q->proximo = pilha.inicio;
        p->anterior = q;
        pilha.inicio = q;

    }
    pilha.cardinalidade++;
}

template<typename T>
void retira(Pilha<T> &pilha)
{
    Nodo<T> *p;
    p = pilha.inicio;
    pilha.inicio = pilha.inicio->proximo;
    delete p;
    pilha.cardinalidade--;
}

template<typename T>
void mostra(Pilha<T> pilha)
{
    for (Nodo<T>* p = pilha.inicio; p != NULL; p = p->proximo)
        cout << "[" << p->elemento << "]";
    cout << endl;
}

template<typename T>
void destroi(Pilha<T> &pilha)
{
    Nodo<T> *p;
    while (pilha.inicio != NULL)
    {
        p = pilha.inicio;
        pilha.inicio = pilha.inicio->proximo;
        delete p;
    }
    pilha.cardinalidade = 0;
}

#endif // PILHA_H_INCLUDED
