#include <iostream>
#include <stdlib.h>
#define TMAX 30
using namespace std;
using std::basic_string;    // classe para aumentar as sequ�ncias do tipo 'char' - .length() -> tamanho da string

// REGISTRO DO EMPR�STIMO
typedef struct
{
    string matricula, isbn, dataDev;
    int codigo;
} Emprestimo;

// REGISTRO DO LIVRO
typedef struct
{
    string titulo, autor, isbn;
    int quantDisp, quantExemp;
} Livro;

// MENU DO ACERVO VIRTUAL
int menu(int choice){
        cout << "-----MENU-----";
        cout << "\n1 - INCLUS�O DE UM LIVRO";
        cout << "\n2 - CONSULTA DE UM LIVRO";
        cout << "\n3 - LIVROS DO ACERVO";
        cout << "\n4 - EMPR�STIMO DE LIVRO";
        cout << "\n5 - EMPR�STIMOS ATIVOS";
        cout << "\n6 - DEVOLU��O DE UM LIVRO";
        cout << "\n7 - EXCLUS�O DE UM LIVRO";
        cout << "\n8 - SAIR" << endl;
        cin >> choice;
        return choice;
}

// ORDENA OS ISBNs EM ORDEM CRESCENTE
void ordenaAcervo(int n, Livro acervo[]){
    int i, j;
    Livro auxilio;  // vari�vel auxiliar
    for(i=0;i<n-1;i++){
        int menor=i;
        for(j=i+1;j<n;j++)
            if(acervo[j].isbn<acervo[menor].isbn)
                menor=j;

        auxilio=acervo[i];
        acervo[i]=acervo[menor];
        acervo[menor]=auxilio;
    }
}

// RELAT�RIO 1 - LIVROS NO ACERVO COM SUAS RESPECTIVAS INFORMA��ES
void livrosAcervo(int n, Livro acervo[]){
    int i;
    cout << "LIVROS NO ACERVO" << endl;
    for(i=0;i<n;i++){
        cout << "\nISBN: " << acervo[i].isbn << endl;
        cout << "T�tulo: " << acervo[i].titulo << endl;
        cout << "Autor: " << acervo[i].autor << endl;
        cout << "Quantidade de exemplares: " << acervo[i].quantExemp << endl;
        cout << "Quantidade dispon�vel: " << acervo[i].quantDisp << endl;
        cout << endl;
    }
}

// RELAT�RIO 2 - EMPR�STIMOS ATIVOS COM SUAS RESPECTIVAS INFORMA��ES
void emprestimosAtivos(int m, Emprestimo ativos[]){
	int i;
	cout << "EMPR�STIMOS ATIVOS" << endl;
	for(i=0;i<m;i++){
        cout << "\nISBN do livro: " << ativos[i].isbn << endl;
		cout << "Matr�cula: " << ativos[i].matricula << endl;
		cout << "Data de devolu��o: " << ativos[i].dataDev << endl;
        cout << "C�digo do empr�stimo: " << ativos[i].codigo << endl;
        cout << endl;
	}
}

// CONSULTA UM LIVRO PELO ISBN
void consultaLivro(string isbn, int n, Livro acervo[]){
    int i;
    bool resp=false;
    cout << "CONSULTA DE UM LIVRO" << endl;
	cout << "\nInforme o ISBN: ";
	cin.ignore();
	getline(cin,isbn);
    for(i=0; i<n; i++){
        if(isbn==acervo[i].isbn){   // valida se o livro (isbn) existe no acervo
            cout << "\nISBN: " << acervo[i].isbn << endl;
            cout << "T�tulo: " << acervo[i].titulo << endl;
            cout << "Autor: " << acervo[i].autor << endl;
            cout << "Quantidade de exemplares: " << acervo[i].quantExemp << endl;
            cout << "Quantidade dispon�vel: " << acervo[i].quantDisp << endl;
            resp=true;
            break;
        }
    }
    if(resp==false) // falso = isbn n�o encontrado
        cout << "\nT�tulo inexistente." << endl;
}

// INCLUI UM LIVRO PELAS SUAS INFORMA��ES
void inclusaoLivro(int &n, Livro acervo[]){
    Livro dados;
    string isbn;
    int i;
	bool resp=false;
    cout << "INCLUS�O DE UM LIVRO" << endl;
    do{
        cout << "\nInforme o ISBN (13 d�gitos): ";
        cin.ignore();
        getline(cin,isbn);
    }while(isbn.length()!=13);   // valida��o do n�mero de caracteres para o isbn - quant = 13
                                // o ISBN n�o pode ter um tamanho inferior nem superior a 13 d�gitos
    for(i=0;i<n;i++){
        if(isbn==acervo[i].isbn){   // valida se o isbn j� existe
            cout << "\nT�tulo j� existente." << endl;
            resp=true;  // se o isbn for encontrado no acervo, ent�o � verdadeiro o livro j� existe
            break;      // e o programa n�o executa os pr�ximos comandos desta subrotina
        }
    }
    if(resp==false){    // caso o isbn n�o exista, executa
        dados.isbn=isbn;
        do{
            cout << "Informe o t�tulo: ";
            getline(cin,dados.titulo);
        }while(dados.titulo.size()==0); // valida��o para que n�o aceite espa�o em branco
        do{
            cout << "Informe o autor: ";
            getline(cin,dados.autor);
        }while(dados.autor.size()==0); // valida��o para que n�o aceite espa�o em branco
        do{
            cout << "Quantidade de exemplares: ";
            cin >> dados.quantExemp;
        }while(dados.quantExemp<1); // valida��o para que a quantidade de exemplares n�o seja inferior a 1
        do{
            cout << "Quantidade dispon�vel para empr�stimo: ";
            cin >> dados.quantDisp;
        }while(dados.quantDisp<1 or dados.quantDisp>dados.quantExemp);  // valida��o para que a quantidade dispon�vel n�o seja
                                                                        // inferior a 1 nem superior a quantidade de exemplares

        acervo[n]=dados;    // guarda as informa��es do livro no vetor do tipo Livro
        n++;
        cout << "\nInclus�o de t�tulo confirmada." << endl;
    }
}

// EMPR�STIMO DE UM LIVRO GERANDO UM C�DIGO QUE CORRESPONDE AO SEU �NDICE
void emprestimoLivro(int n, Livro acervo[], int &m, Emprestimo ativos[]){
    Emprestimo dados;
    string isbn;
	int i, codigo;
	bool resp=false;
    cout << "EMPR�STIMO DE LIVRO" << endl;
    cout << "\nInforme o ISBN: ";
    cin.ignore();
    getline(cin,isbn);
	for(i=0;i<n;i++){
	    if(isbn==acervo[i].isbn){   // valida se o isbn existe
			resp=true;  //caso exista, ent�o � verdadeiro
			break;
	    }
	}
    if(resp==true){
		if(acervo[i].quantDisp>0){  // valida se h� quantidade dispon�vel para empr�stimo
            dados.isbn=isbn;
            do{
                cout << "Informe a matr�cula: ";
                getline(cin,dados.matricula);
	        }while(dados.matricula.length()!=4); // valida��o do n�mero de caracteres para a matr�cula - quant = 4
	        do{
                cout << "Informe a data de devolu��o: ";
                getline(cin,dados.dataDev);
            }while(dados.dataDev.size()==0); // valida��o para que n�o aceite espa�o em branco
            dados.codigo=m;     // gera o c�digo acrecsentando 1 a cada empr�stimo
			acervo[i].quantDisp--;  // decrementa 1 a quantidade dispon�vel
			ativos[m]=dados;    // guarda as informa��es do empr�stimo no vetor do tipo Empr�stimo
			m++;
			cout << "\nEmpr�stimo Realizado. C�digo: " << dados.codigo << endl;
		}else   // caso n�o exista quantidade dispon�vel para empr�stimo
	        cout << "\nExemplar indispon�vel para empr�stimo." << endl;

    }else   // caso o isbn n�o exista
        cout << "\nT�tulo inexistente." << endl;
}

// EXCUI UM LIVRO PELO ISBN
void exclusaoLivro(int &n, Livro acervo[]){
    int i, j;
    string isbn;
    bool resp=false;
    cout << "EXCLUS�O DE UM LIVRO" << endl;
	cout << "\nInforme o ISBN: ";
	cin.ignore();
	getline(cin,isbn);
    for(i=0;i<n;i++){
        if(isbn==acervo[i].isbn){   // valida se o isbn (livro) existe
            acervo[i]=acervo[n-1]; // posi��o encontrada = quantidade de livros - 1
            n--;
        cout << "\nExclus�o realizada." << endl;
        resp=true;  // isbn encontrado
        break;
        }
    }
    if(resp==false) // caso o isbn n�o exista
        cout << "\nT�tulo inexistente. Imposs�vel excluir." << endl;
}

// DEVOLVE O LIVRO PELO C�DIGO DO EMPR�STIMO
void devolucaoLivro(int n, Livro acervo[], int m, Emprestimo ativos[]){
    int i, j, codigo;
    string isbn;
    bool resp=false;
    cout << "DEVOLU��O DE UM LIVRO" << endl;
	cout << "\nInforme o c�digo do empr�stimo: ";
	cin.ignore();
	cin >> codigo;
	for(i=0;i<m;i++){
        if(codigo==ativos[i].codigo){   // valida se o c�digo do empr�stimo existe
            if(ativos[i].matricula=="-1 (DEVOLVIDO)"){  // valida se o livro j� foi devolvido
                cout << "\nDevolu��o j� realizada." << endl;
            }else{      // caso n�o tenha sido devolvido
                for(j=0;j<n;j++){
                    if(acervo[j].isbn==ativos[i].isbn){     // valida se o isbn (livro) foi emprestado
                        acervo[j].quantDisp++;      // acrescenta 1 a quantidade dispon�vel
                        ativos[i].matricula="-1 (DEVOLVIDO)";   // acrescenta -1 � matr�cula
                        cout << "\nDevolu��o realizada." << endl;
                        break;
                    }
                }
            }
        resp=true;  // c�digo encontrado
        break;
        }
    }
	if(resp==false)     // caso n�o tenha registros de que o livro tenha sido emprestado
        cout << "\nRegistro inexistente." << endl;
}
// PRINCIPAL - CHAMADA DAS SUBROTINAS
int main()
{
    string isbn;
    int n=0, m=0, choice;
    Livro acervo[TMAX];
    Emprestimo ativos[TMAX];

    do{
        ordenaAcervo(n,acervo);     // chama a subrotina para ordenar os livros
        choice=menu(choice);       // chama o MENU com as op��es
        switch(choice){           // 'switch case' ativa chamando as subrotinas correspondentes �s op��es
            case 1:
                system("cls");
                inclusaoLivro(n,acervo);
                system("pause");
                break;

            case 2:
                system("cls");
                consultaLivro(isbn,n,acervo);
                system("pause");
                break;

            case 3:
                system("cls");
                livrosAcervo(n,acervo);
                system("pause");
                break;

            case 4:
                system("cls");
                emprestimoLivro(n,acervo,m,ativos);
                system("pause");
                break;

            case 5:
                system("cls");
                emprestimosAtivos(m,ativos);
                system("pause");
                break;

            case 6:
                system("cls");
                devolucaoLivro(n,acervo,m,ativos);
                system("pause");
                break;

            case 7:
                system("cls");
                exclusaoLivro(n,acervo);
                system("pause");
                break;
        }

    system("cls");
    }while(choice!=8);   // enquanto a op��o for diferente de 8, o loop continuar�

    system("cls");
    cout << "\nAt� breve..." << endl;   // encerramento do programa

    return 0;
}
