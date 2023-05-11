#include <iostream>
#include "Pilha.h"
#include "Calculadora.h"
#include "Validacao.h"
using namespace std;

int main()
{
    string numero, palavra, opcao;
    float valorAtual, valorAnterior = 0.0, resultado;
    Pilha<float> pilha;

    inicia(pilha);
    insere(pilha, valorAnterior);

    do
    {
        bool verificado = true;
        cout<<"-------------------Menu-------------------\n"
            "Informe por escrito a operacao e o valor entre parenteses:\n"
            "  ZERA\n"
            "  SOMA(valor)\n"
            "  SUBTRAI(valor)\n"
            "  MULTIPLICA(valor)\n"
            "  DIVIDE(valor)\n"
            "  PARCELAS\n"
            "  IGUAL\n"
            "  FIM\n"
            "------------------------------------------\n";
        getline(cin,opcao);
        toUpper(opcao);
        system("cls");

        try
        {
            palavra = verificaSeDiferenteDeLetra(opcao);
        }
        catch (const char* msg)
        {
            cerr << msg << endl;
            verificado = false;
        }

        try
        {
            numero = verificaSeDiferenteDeNumero(opcao);
        }
        catch (const char* msg)
        {
            cerr << msg << endl;
            verificado = false;
        }

        valorAtual = converteStringParaFloat(numero);

        if(verificado)
        {
            if(palavra == "ZERA")
            {
                zera(pilha);
                cout << "Pilha (re)inicializada.\n";
            }
            if(palavra == "SOMA")
            {
                cout << "ADICAO\n";
                resultado = soma(valorAtual, valorAnterior);
                valorAnterior = resultado;
                insere(pilha, resultado);
                cout << "\nValor adicionado.\n";
            }
            if(palavra == "SUBTRAI")
            {
                cout << "SUBTRACAO\n";
                resultado = subtrai(valorAtual, valorAnterior);
                valorAnterior = resultado;
                insere(pilha, resultado);
                cout << "\nValor subtraido.\n";
            }
            if(palavra == "MULTIPLICA")
            {
                cout << "MULTIPLICACAO\n";
                resultado = multiplica(valorAtual, valorAnterior);
                valorAnterior = resultado;
                insere(pilha, resultado);
                cout << "\nValor multiplicado.\n";
            }
            if(palavra == "DIVIDE")
            {
                cout << "DIVISAO\n";
                resultado = divide(valorAtual, valorAnterior);
                valorAnterior = resultado;
                insere(pilha, resultado);
                cout << "\nValor dividido.\n";
            }
            if(palavra == "PARCELAS")
            {
                cout << "PARCELAS\n";
                if(pilha.cardinalidade > 2)
                    parcelas(pilha);
                else
                    cout << "\nNao ha parcelas para apresentar no momento.\n";

            }
            if(palavra == "IGUAL")
            {
                resultado = igual(pilha);
                cout << "Resultado = " << resultado << endl;
            }
            if(palavra == "FIM")
            {
                cout << "Saindo...\n";
            }
            cout << endl;
        }
        system("pause");
        system("cls");
    }
    while(opcao != "FIM");


    destroi(pilha);

    return 0;
}
