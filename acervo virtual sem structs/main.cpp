#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cctype>
#define TMAX 50
using namespace std;

int menu();
void ordenaAcervo(int,string[],string[],string[],string[],int[]);
int pesquisaISBNeRetornaPos(int,string,string);
bool validacaoVazio(string);
bool verificaSeDifDig(string);
bool verificaSeDifLet(string);
bool validacaoISBN(string);
void toUpperNomes(string&);
bool validacaoNomeAutor(string);
bool validacaoQuant(int);
void inclusaoLivro(int&,string[],string[],string[],string[],int[]);
void consultaLivro(int,string[],string[],string[],string[],int[]);
void exclusaoLivro(int&,string[],string[],string[],string[],int[]);
void aquisicaoLivro(int,string[],int[]);
void relatorioAcervo(int,string[],string[],string[],string[],int[]);

int main()
{
    string titulo[TMAX], autor[TMAX], editora[TMAX], isbn[TMAX];
    int quant[TMAX], n=0, resp;

    do{
        resp=menu();
        switch(resp){

            case 1:
                system("cls");
                inclusaoLivro(n,titulo,autor,editora,isbn,quant);
                system("pause");
                break;
            case 2:
                system("cls");
                consultaLivro(n,titulo,autor,editora,isbn,quant);
                system("pause");
                break;
            case 3:
                system("cls");
                exclusaoLivro(n,titulo,autor,editora,isbn,quant);
                system("pause");
                break;
            case 4:
                system("cls");
                aquisicaoLivro(n,isbn,quant);
                system("pause");
                break;
            case 5:
                system("cls");
                relatorioAcervo(n,titulo,autor,editora,isbn,quant);
                system("pause");
        }
        ordenaAcervo(n,titulo,autor,editora,isbn,quant);
        system("cls");
    }while(resp!=6);


    return 0;
}

int menu(){
    int choice;
    cout << "-----------MENU------------";
    cout << "\n1 - INCLUSÃO DE UM LIVRO";
    cout << "\n2 - CONSULTA DE UM LIVRO";
    cout << "\n3 - EXCLUSÃO DE UM LIVRO";
    cout << "\n4 - AQUISIÇÃO DE UM LIVRO";
    cout << "\n5 - RELATÓRIO DO ACERVO";
    cout << "\n6 - SAIR" << endl;
    cin >> choice;
    return choice;
}

void ordenaAcervo(int n, string titulo[], string autor[], string editora[], string isbn[], int quant[])
{
    string aux1;
    int i, j, menor, aux2;
    for(i=0;i<n-1;i++){
        menor=i;
        for(j=i+1;j<n;j++)
            if(titulo[j]<titulo[menor])
            menor=j;

        aux1=titulo[i];
        titulo[i]=titulo[menor];
        titulo[menor]=aux1;

        aux1=isbn[i];
        isbn[i]=isbn[menor];
        isbn[menor]=aux1;

        aux1=autor[i];
        autor[i]=autor[menor];
        autor[menor]=aux1;

        aux1=editora[i];
        editora[i]=editora[menor];
        editora[menor]=aux1;

        aux2=quant[i];
        quant[i]=quant[menor];
        quant[menor]=aux2;
    }
}

int pesquisaISBNeRetornaPos(int n, string aux, string isbn[])
{
    for(int i=0;i<n;i++)
        if(aux==isbn[i])
            return i;
    return -1;
}

bool validacaoVazio(string aux)
{
    if(aux.size()==0)
        return false;
    return true;
}

bool verificaSeDifDig(string aux)
{
    for(unsigned int i=0;i<aux.size();i++)
        if(!isdigit(aux.at(i)))
            return true;
    return false;
}

bool verificaSeDifLet(string aux)
{
    for(unsigned int i=0;i<aux.size();i++)
        if(!isalpha(aux.at(i)))
            return true;
    return false;
}

bool validacaoISBN(string aux)
{
    bool resp;
    if(aux.size()!=4)
        return false;
    resp=verificaSeDifDig(aux);
    if(resp)
        return false;
    return true;
}

void toUpperNomes(string &aux)
{
    char a;
    string aux2="";
    for(unsigned int i=0;i<aux.size();i++){
        a=toupper(aux[i]);
        aux2+=a;
    }
    aux=aux2;
}

bool validacaoNomeAutor(string aux)
{
    if(aux.size()<2)
        return false;
    for(unsigned int i=0;i<aux.size();i++)
        if(!isalpha(aux.at(i)) && aux.at(i)!=' ')
            return false;
    return true;
}

bool validacaoQuant(int aux)
{
    if(aux<1)
        return false;
    return true;
}

void inclusaoLivro(int &n, string titulo[], string autor[], string editora[], string isbn[], int quant[])
{
    string aux;
    int auxNum, pos;
    bool resp, resp2;

    cout << "PARA INCLUIR NOVO LIVRO, INFORME:" << endl;
    cin.ignore();
    do{
        cout << "ISBN: ";
        getline(cin,aux);
        resp=validacaoVazio(aux);
        resp2=validacaoISBN(aux);
        if(!resp || !resp2)
            cout << "Inconsistência(s) encontrada(s). Tente novamente." << endl;
    }while(!resp || !resp2);
    pos=pesquisaISBNeRetornaPos(n,aux,isbn);
    if(pos==-1){
        isbn[n]=aux;
        do{
            cout << "TÍTULO: ";
            getline(cin,aux);
            resp=validacaoVazio(aux);
            if(!resp)
                cout << "Inconsistência(s) encontrada(s). Tente novamente." << endl;
        }while(!resp);
        toUpperNomes(aux);
        titulo[n]=aux;

        do{
            cout << "AUTOR: ";
            getline(cin,aux);
            resp=validacaoVazio(aux);
            resp2=validacaoNomeAutor(aux);
            if(!resp || !resp2)
                    cout << "Inconsistência(s) encontrada(s). Tente novamente." << endl;
        }while(!resp || !resp2);
        toUpperNomes(aux);
        autor[n]=aux;

        do{
            cout << "EDITORA: ";
            getline(cin,aux);
            resp=validacaoVazio(aux);
            resp2=verificaSeDifLet(aux);
            if(!resp || resp2)
                cout << "Inconsistência(s) encontrada(s). Tente novamente." << endl;
        }while(!resp || resp2);
        toUpperNomes(aux);
        editora[n]=aux;

        do{
            cout << "QUANTIDADE: ";
            getline(cin,aux);
            resp=verificaSeDifDig(aux);
            if(resp)
                cout << "Inconsistência(s) encontrada(s). Tente novamente." << endl;
            else{
                auxNum=atoi(aux.c_str());
                resp2=validacaoQuant(auxNum);
                if(!resp2)
                    cout << "Inconsistência(s) encontrada(s). Tente novamente." << endl;
            }
        }while(resp || !resp2);
        quant[n]=auxNum;

        n++;
        cout << "Inclusão de título confirmada." << endl;
    }
    else
        cout << "Livro já existente." << endl;
}

void consultaLivro(int n, string titulo[], string autor[], string editora[], string isbn[], int quant[])
{
    string aux;
    int pos;
    bool resp, resp2;
    cin.ignore();
    do{
        cout << "Informe o ISBN: ";
        getline(cin,aux);
        resp=validacaoVazio(aux);
        resp2=validacaoISBN(aux);
        if(!resp || !resp2)
                cout << "Inconsistência(s) encontrada(s). Tente novamente." << endl;
    }while(!resp || !resp2);
    pos=pesquisaISBNeRetornaPos(n,aux,isbn);
    if(pos!=-1){
        cout << "\nISBN: " << isbn[pos] << endl;
        cout << "TÍTULO: " << titulo[pos] << endl;
        cout << "AUTOR: " << autor[pos] << endl;
        cout << "EDITORA: " << editora[pos] << endl;
        cout << "QUANTIDADE: " << quant[pos] << endl;
        cout << endl;
    }
    else
        cout << "Livro inexistente." << endl;
}

void exclusaoLivro(int &n, string titulo[], string autor[], string editora[], string isbn[], int quant[])
{
    string aux;
    int pos;
    bool resp, resp2;
    cin.ignore();
    do{
        cout << "Informe o ISBN: ";
        getline(cin,aux);
        resp=validacaoVazio(aux);
        resp2=validacaoISBN(aux);
        if(!resp || !resp2)
            cout << "Inconsistência(s) encontrada(s). Tente novamente." << endl;
    }while(!resp || !resp2);
    pos=pesquisaISBNeRetornaPos(n,aux,isbn);
    if(pos!=-1){
        isbn[pos]=isbn[n-1];
        titulo[pos]=titulo[n-1];
        autor[pos]=autor[n-1];
        editora[pos]=editora[n-1];
        quant[pos]=quant[n-1];
        n--;
        cout << "Livro excluído." << endl;
    }
    else
        cout << "Livro inexistente, impossível excluir." << endl;
}

void aquisicaoLivro(int n, string isbn[], int quant[])
{
    string aux;
    int auxNum, pos;
    bool resp, resp2;
    cin.ignore();
    do{
        cout << "Informe o ISBN: ";
        getline(cin,aux);
        resp=validacaoISBN(aux);
        resp2=verificaSeDifDig(aux);
        if(!resp || resp2)
            cout << "Inconsistência(s) encontrada(s). Tente novamente." << endl;
    }while(!resp || resp2);
    pos=pesquisaISBNeRetornaPos(n,aux,isbn);
    if(pos!=-1){
        do{
            cout << "QUANTIDADE DE EXEMPLARES ADQUIRIDOS: ";
            getline(cin,aux);
            resp=verificaSeDifDig(aux);
            if(resp)
                cout << "Inconsistência(s) encontrada(s). Tente novamente." << endl;
            else{
                auxNum=atoi(aux.c_str());
                resp2=validacaoQuant(auxNum);
                if(!resp2)
                    cout << "Inconsistência(s) encontrada(s). Tente novamente." << endl;
            }
        }while(resp || !resp2);
        quant[pos]+=auxNum;
        cout << "Exemplares incluídos." << endl;
    }
    else
        cout << "Livro inexistente." << endl;
}

void relatorioAcervo(int n, string titulo[], string autorRef[], string editora[], string isbn[], int quant[])
{
    cout << "LIVROS NO ACERVO" << endl;
    for(int i=0;i<n;i++){
        cout << "\nISBN: " << isbn[i] << endl;
        cout << "TÍTULO: " << titulo[i] << endl;
        cout << "AUTOR: " <<  autorRef[i] << endl;
        cout << "EDITORA: " << editora[i] << endl;
        cout << "QUANTIDADE: " << quant[i] << endl;
        cout << endl;
    }
}
