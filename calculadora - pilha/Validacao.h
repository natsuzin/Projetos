#ifndef VALIDACAO_H_INCLUDED
#define VALIDACAO_H_INCLUDED
#include <cstring>
#include <iostream>

void toUpper(string &aux)
{
    char a;
    string aux2="";
    for(unsigned int i=0; i<aux.size(); i++)
    {
        a=toupper(aux.at(i));
        aux2+=a;
    }
    aux=aux2;
}

void validaSeVazio(string aux)
{
    if(aux.size()==0){
        throw "INFORME A EXPRESSAO E O VALOR.";
    }
}

string verificaSeDiferenteDeNumero(string aux)
{
    string numero="";
    for(unsigned int i=0; i<aux.size(); i++)
    {
        if(aux.at(i) == '(')
        {
            i++;
            if(aux.at(i) == ')'){
                throw "INFORME O VALOR JUNTO A EXPRESSAO.";
            }
            for(unsigned int j=i; j<aux.size(); j++)
            {
                if(!isdigit(aux.at(j)))
                {
                    if(aux.at(j) == ')')
                        return numero;
                    else{
                        if(aux.at(j) == '.')
                            numero = numero + aux.at(j);
                        else{
                            if(aux.at(j) == '-')
                                numero = numero + aux.at(j);
                            else
                                throw "VALOR INCORRETO.";
                        }
                    }
                }
                else{
                    numero = numero + aux.at(j);
                }
            }
        }
    }
}

string verificaSeDiferenteDeLetra(string aux)
{
    string palavra = "";
    for(unsigned int i=0; i<aux.size(); i++)
    {
        palavra = palavra + aux.at(i);
        if(palavra == "ZERA") return palavra;
        if(palavra == "SOMA") return palavra;
        if(palavra == "SUBTRAI") return palavra;
        if(palavra == "MULTIPLICA") return palavra;
        if(palavra == "DIVIDE") return palavra;
        if(palavra == "PARCELAS") return palavra;
        if(palavra == "IGUAL") return palavra;
        if(palavra == "FIM") return palavra;
        if(!isalpha(aux.at(i))) throw "COMANDO INVÁLIDO.";
    }
    throw "COMANDO INVÁLIDO.";
}

float converteStringParaFloat(string aux)
{
    float valor;
    valor=atoi(aux.c_str());
    return valor;
}

#endif // VALIDACAO_H_INCLUDED
