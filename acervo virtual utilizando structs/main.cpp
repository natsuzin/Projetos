#include <iostream>
#include <stdlib.h>
#define TMAX 30
using namespace std;
using std::basic_string;    // classe para aumentar as sequências do tipo 'char' - .length() -> tamanho da string

// REGISTRO DO EMPRÉSTIMO
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
        cout << "\n1 - INCLUSÃO DE UM LIVRO";
        cout << "\n2 - CONSULTA DE UM LIVRO";
        cout << "\n3 - LIVROS DO ACERVO";
        cout << "\n4 - EMPRÉSTIMO DE LIVRO";
        cout << "\n5 - EMPRÉSTIMOS ATIVOS";
        cout << "\n6 - DEVOLUÇÃO DE UM LIVRO";
        cout << "\n7 - EXCLUSÃO DE UM LIVRO";
        cout << "\n8 - SAIR" << endl;
        cin >> choice;
        return choice;
}

// ORDENA OS ISBNs EM ORDEM CRESCENTE
void ordenaAcervo(int n, Livro acervo[]){
    int i, j;
    Livro auxilio;  // variável auxiliar
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

// RELATÓRIO 1 - LIVROS NO ACERVO COM SUAS RESPECTIVAS INFORMAÇÕES
void livrosAcervo(int n, Livro acervo[]){
    int i;
    cout << "LIVROS NO ACERVO" << endl;
    for(i=0;i<n;i++){
        cout << "\nISBN: " << acervo[i].isbn << endl;
        cout << "Título: " << acervo[i].titulo << endl;
        cout << "Autor: " << acervo[i].autor << endl;
        cout << "Quantidade de exemplares: " << acervo[i].quantExemp << endl;
        cout << "Quantidade disponível: " << acervo[i].quantDisp << endl;
        cout << endl;
    }
}

// RELATÓRIO 2 - EMPRÉSTIMOS ATIVOS COM SUAS RESPECTIVAS INFORMAÇÕES
void emprestimosAtivos(int m, Emprestimo ativos[]){
	int i;
	cout << "EMPRÉSTIMOS ATIVOS" << endl;
	for(i=0;i<m;i++){
        cout << "\nISBN do livro: " << ativos[i].isbn << endl;
		cout << "Matrícula: " << ativos[i].matricula << endl;
		cout << "Data de devolução: " << ativos[i].dataDev << endl;
        cout << "Código do empréstimo: " << ativos[i].codigo << endl;
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
            cout << "Título: " << acervo[i].titulo << endl;
            cout << "Autor: " << acervo[i].autor << endl;
            cout << "Quantidade de exemplares: " << acervo[i].quantExemp << endl;
            cout << "Quantidade disponível: " << acervo[i].quantDisp << endl;
            resp=true;
            break;
        }
    }
    if(resp==false) // falso = isbn não encontrado
        cout << "\nTítulo inexistente." << endl;
}

// INCLUI UM LIVRO PELAS SUAS INFORMAÇÕES
void inclusaoLivro(int &n, Livro acervo[]){
    Livro dados;
    string isbn;
    int i;
	bool resp=false;
    cout << "INCLUSÃO DE UM LIVRO" << endl;
    do{
        cout << "\nInforme o ISBN (13 dígitos): ";
        cin.ignore();
        getline(cin,isbn);
    }while(isbn.length()!=13);   // validação do número de caracteres para o isbn - quant = 13
                                // o ISBN não pode ter um tamanho inferior nem superior a 13 dígitos
    for(i=0;i<n;i++){
        if(isbn==acervo[i].isbn){   // valida se o isbn já existe
            cout << "\nTítulo já existente." << endl;
            resp=true;  // se o isbn for encontrado no acervo, então é verdadeiro o livro já existe
            break;      // e o programa não executa os próximos comandos desta subrotina
        }
    }
    if(resp==false){    // caso o isbn não exista, executa
        dados.isbn=isbn;
        do{
            cout << "Informe o título: ";
            getline(cin,dados.titulo);
        }while(dados.titulo.size()==0); // validação para que não aceite espaço em branco
        do{
            cout << "Informe o autor: ";
            getline(cin,dados.autor);
        }while(dados.autor.size()==0); // validação para que não aceite espaço em branco
        do{
            cout << "Quantidade de exemplares: ";
            cin >> dados.quantExemp;
        }while(dados.quantExemp<1); // validação para que a quantidade de exemplares não seja inferior a 1
        do{
            cout << "Quantidade disponível para empréstimo: ";
            cin >> dados.quantDisp;
        }while(dados.quantDisp<1 or dados.quantDisp>dados.quantExemp);  // validação para que a quantidade disponível não seja
                                                                        // inferior a 1 nem superior a quantidade de exemplares

        acervo[n]=dados;    // guarda as informações do livro no vetor do tipo Livro
        n++;
        cout << "\nInclusão de título confirmada." << endl;
    }
}

// EMPRÉSTIMO DE UM LIVRO GERANDO UM CÓDIGO QUE CORRESPONDE AO SEU ÍNDICE
void emprestimoLivro(int n, Livro acervo[], int &m, Emprestimo ativos[]){
    Emprestimo dados;
    string isbn;
	int i, codigo;
	bool resp=false;
    cout << "EMPRÉSTIMO DE LIVRO" << endl;
    cout << "\nInforme o ISBN: ";
    cin.ignore();
    getline(cin,isbn);
	for(i=0;i<n;i++){
	    if(isbn==acervo[i].isbn){   // valida se o isbn existe
			resp=true;  //caso exista, então é verdadeiro
			break;
	    }
	}
    if(resp==true){
		if(acervo[i].quantDisp>0){  // valida se há quantidade disponível para empréstimo
            dados.isbn=isbn;
            do{
                cout << "Informe a matrícula: ";
                getline(cin,dados.matricula);
	        }while(dados.matricula.length()!=4); // validação do número de caracteres para a matrícula - quant = 4
	        do{
                cout << "Informe a data de devolução: ";
                getline(cin,dados.dataDev);
            }while(dados.dataDev.size()==0); // validação para que não aceite espaço em branco
            dados.codigo=m;     // gera o código acrecsentando 1 a cada empréstimo
			acervo[i].quantDisp--;  // decrementa 1 a quantidade disponível
			ativos[m]=dados;    // guarda as informações do empréstimo no vetor do tipo Empréstimo
			m++;
			cout << "\nEmpréstimo Realizado. Código: " << dados.codigo << endl;
		}else   // caso não exista quantidade disponível para empréstimo
	        cout << "\nExemplar indisponível para empréstimo." << endl;

    }else   // caso o isbn não exista
        cout << "\nTítulo inexistente." << endl;
}

// EXCUI UM LIVRO PELO ISBN
void exclusaoLivro(int &n, Livro acervo[]){
    int i, j;
    string isbn;
    bool resp=false;
    cout << "EXCLUSÃO DE UM LIVRO" << endl;
	cout << "\nInforme o ISBN: ";
	cin.ignore();
	getline(cin,isbn);
    for(i=0;i<n;i++){
        if(isbn==acervo[i].isbn){   // valida se o isbn (livro) existe
            acervo[i]=acervo[n-1]; // posição encontrada = quantidade de livros - 1
            n--;
        cout << "\nExclusão realizada." << endl;
        resp=true;  // isbn encontrado
        break;
        }
    }
    if(resp==false) // caso o isbn não exista
        cout << "\nTítulo inexistente. Impossível excluir." << endl;
}

// DEVOLVE O LIVRO PELO CÓDIGO DO EMPRÉSTIMO
void devolucaoLivro(int n, Livro acervo[], int m, Emprestimo ativos[]){
    int i, j, codigo;
    string isbn;
    bool resp=false;
    cout << "DEVOLUÇÃO DE UM LIVRO" << endl;
	cout << "\nInforme o código do empréstimo: ";
	cin.ignore();
	cin >> codigo;
	for(i=0;i<m;i++){
        if(codigo==ativos[i].codigo){   // valida se o código do empréstimo existe
            if(ativos[i].matricula=="-1 (DEVOLVIDO)"){  // valida se o livro já foi devolvido
                cout << "\nDevolução já realizada." << endl;
            }else{      // caso não tenha sido devolvido
                for(j=0;j<n;j++){
                    if(acervo[j].isbn==ativos[i].isbn){     // valida se o isbn (livro) foi emprestado
                        acervo[j].quantDisp++;      // acrescenta 1 a quantidade disponível
                        ativos[i].matricula="-1 (DEVOLVIDO)";   // acrescenta -1 à matrícula
                        cout << "\nDevolução realizada." << endl;
                        break;
                    }
                }
            }
        resp=true;  // código encontrado
        break;
        }
    }
	if(resp==false)     // caso não tenha registros de que o livro tenha sido emprestado
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
        choice=menu(choice);       // chama o MENU com as opções
        switch(choice){           // 'switch case' ativa chamando as subrotinas correspondentes às opções
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
    }while(choice!=8);   // enquanto a opção for diferente de 8, o loop continuará

    system("cls");
    cout << "\nAté breve..." << endl;   // encerramento do programa

    return 0;
}
