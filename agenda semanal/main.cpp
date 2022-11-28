#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <string>
#define tsem 7
#define tmax 6
using namespace std;

typedef struct{
    string hinicial, hfinal, tipo, local, asst;
}Compromisso;

typedef struct{
    string dma, diasem;
    int m;
    Compromisso comp[tmax];
}Agenda;

char menu();
void toUpper(string&);
bool validacaoVazio(string);
bool verificaSeDifDig(string);
bool verificaSeDifLet(string);
void diasSemana(Agenda[]);
void converteMes(string&);
bool validaData(string,string);
bool validaHora(string);
bool validaHoraInicialxFinal(string,string);
int pesquisaDataERetornaPos(int,Agenda[],string);
int pesquisaHoraERetornaPos(int,Agenda[],string,int);
int pesquisaHoraFinalERetornaPos(int,Agenda[],string,int);
int ordenaComp(Agenda[],int,int,int,int);
string entradaDeDadosData();
void iniciaSemana(Agenda[]);
void incluiCompromisso(Agenda[]);
void excluiCompromisso(Agenda[]);
void relatorio1(Agenda[]);
void relatorio2(Agenda[]);

int main()
{
    char ch;
    bool resp;
    Agenda data[tsem];

    do{
        system("cls");
        diasSemana(data);
        do{
            resp=true;
            ch=menu();
            if(!isdigit(ch)){
                resp=false;
                system("cls");
                cout << "Tente novamente." << endl;
                system("pause");
                system("cls");
            }
        }while(!resp);
        system("cls");
        switch(ch){
            case '1':
                cin.ignore();
                iniciaSemana(data);
                system("pause");
                break;
            case '2':
                cin.ignore();
                incluiCompromisso(data);
                system("pause");
                break;
            case '3':
                cin.ignore();
                excluiCompromisso(data);
                system("pause");
                break;
            case '4':
                cin.ignore();
                relatorio1(data);
                system("pause");
                break;
            case '5':
                cin.ignore();
                relatorio2(data);
                system("pause");
                break;
            default:
                if(ch!='6'){
                    system("cls");
                    cin.ignore();
                    cout << "Tente novamente." << endl;
                    system("pause");
                }
        }
        system("cls");
    }while(ch!='6');
    cout << "Boa semana!";
    return 0;
}

char menu(){
    char ch;
    cout << "_________________MENU_________________";
    cout << "\n1 - INICIAR NOVA SEMANA";
    cout << "\n2 - INCLUIR COMPROMISSO";
    cout << "\n3 - EXCLUIR COMPROMISSO";
    cout << "\n4 - RELATORIO 1: COMPROMISSOS DO DIA";
    cout << "\n5 - RELATORIO 2: AGENDA SEMANAL";
    cout << "\n6 - SAIR" << endl;
    cin >> ch;
    return ch;
}

void toUpper(string &aux){
    char a;
    string aux2="";
    for(unsigned int i=0;i<aux.size();i++){
        a=toupper(aux[i]);
        aux2+=a;
    }
    aux=aux2;
}

bool validacaoVazio(string aux){
    if(aux.size()==0) return false;
    return true;
}

bool verificaSeDifDig(string aux){
    for(unsigned int i=0;i<aux.size();i++)
        if(!isdigit(aux.at(i))) return false;
    return true;
}

bool verificaSeDifLet(string aux){
    for(unsigned int i=0;i<aux.size();i++)
        if(!isalpha(aux.at(i))) return false;
    return true;
}

void diasSemana(Agenda data[]){
    data[0].diasem="DOMINGO";
    data[1].diasem="SEGUNDA";
    data[2].diasem="TERCA";
    data[3].diasem="QUARTA";
    data[4].diasem="QUINTA";
    data[5].diasem="SEXTA";
    data[6].diasem="SABADO";
}

void converteMes(string &mes){
    if(mes=="JAN") mes="01";
    if(mes=="FEV") mes="02";
    if(mes=="MAR") mes="03";
    if(mes=="ABR") mes="04";
    if(mes=="MAI") mes="05";
    if(mes=="JUN") mes="06";
    if(mes=="JUL") mes="07";
    if(mes=="AGO") mes="08";
    if(mes=="SET") mes="09";
    if(mes=="OUT") mes="10";
    if(mes=="NOV") mes="11";
    if(mes=="DEZ") mes="12";
}

bool validaData(string mes, string dia){
    int dias;
    bool resp;
    resp=validacaoVazio(mes);
    if(!resp) return false;
    resp=validacaoVazio(dia);
    if(!resp) return false;
    resp=verificaSeDifLet(mes);
    if(!resp) return false;
    resp=verificaSeDifDig(dia);
    if(!resp) return false;
    if(dia.size()!=2) return false;
    dias=atoi(dia.c_str());
    if(mes=="JAN" || mes=="MAR" || mes=="MAI" || mes=="JUL" || mes=="AGO" || mes=="OUT" || mes=="DEZ"){
        if(dias<1 || dias>31) return false;
        return true;
    }
    if(mes=="FEV"){
        if(dias<1 || dias>28) return false;
        return true;
    }
    if(mes=="ABR" || mes=="JUN" || mes=="SET" || mes=="NOV"){
        if(dias<1 || dias>30) return false;
        return true;
    }
    return false;
}

bool validaHora(string aux){
    string hora="", minuto="";
    int horas, minutos;
    bool resp;
    resp=validacaoVazio(aux);
    if(!resp) return false;
    if(aux.size()!=5) return false;
    for(unsigned int i=0;i<aux.size();i++)
        if(!isdigit(aux.at(i)) && aux.at(i)!=':') return false;
    hora+=aux.at(0);
    hora+=aux.at(1);
    horas=atoi(hora.c_str());
    minuto+=aux.at(3);
    minuto+=aux.at(4);
    minutos=atoi(minuto.c_str());
    if(horas<0 || horas>23) return false;
    if(minutos<0 || minutos>59) return false;
    return true;
}

bool validaHoraInicialxFinal(string hinicial, string hfinal){
    string hora, minuto;
    int hini, hfin, mini, mfin;

    hora=hinicial.at(0);
    hora+=hinicial.at(1);
    hini=atoi(hora.c_str());
    minuto=hinicial.at(3);
    minuto+=hinicial.at(4);
    mini=atoi(minuto.c_str());
    hora=hfinal.at(0);
    hora+=hfinal.at(1);
    hfin=atoi(hora.c_str());
    minuto=hfinal.at(3);
    minuto+=hfinal.at(4);
    mfin=atoi(minuto.c_str());
    if(mini>=mfin){
        if(hini>=hfin) return false;
        return true;
    }
    else{
        if(hini<=hfin) return true;
        return false;
    }
}

int pesquisaDataERetornaPos(int n, Agenda data[], string aux){
    if(aux==data[n].dma) return n;
    if(n==0) return -1;
    return pesquisaDataERetornaPos(n-1,data,aux);
}

int pesquisaHoraERetornaPos(int n, Agenda data[], string aux, int m)
{
    if(aux==data[n].comp[m].hinicial) return m;
    if(m==0) return -1;
    return pesquisaHoraERetornaPos(n,data,aux,m-1);
}

int pesquisaHoraFinalERetornaPos(int n, Agenda data[], string aux, int m)
{
    if(aux==data[n].comp[m].hfinal) return m;
    if(m==0) return -1;
    return pesquisaHoraFinalERetornaPos(n,data,aux,m-1);
}

int ordenaComp(Agenda data[], int m, int posdia, int i, int j){
    int menor = j;
    Compromisso aux;

    if(m==1) return 0;

    if(data[posdia].comp[i].hinicial<data[posdia].comp[menor].hinicial)
        menor = i;
    aux = data[posdia].comp[i];
    data[posdia].comp[i] = data[posdia].comp[menor];
    data[posdia].comp[menor] = aux;

    return ordenaComp(data,m-1,posdia, i+1, j);
}

string entradaDeDadosData(){
    string mes, dia, aux;
    bool resp;
    cout << "Ano: 2022" << endl;
    do{
        cout << "Informe o mes (formato: tres primeiras letras de cada mes): ";
        getline(cin,mes);
        toUpper(mes);
        cout << "Informe o dia (formato: dois digitos: 01, 02,..., 21, etc): ";
        getline(cin,dia);
        resp=validaData(mes,dia);
        if(!resp) cout << "Dados inconsistentes. Tente novamente." << endl << endl;
    }while(!resp);
    converteMes(mes);
    aux=dia+'/'+mes+'/'+"2022";
    return aux;
}

void iniciaSemana(Agenda data[]){
    char ch;
    string aux, dia="", mes="", ano="2022";
    int dint, mint;
    Agenda auxa;

    do{
        cout << "Confirme sua escolha. Iniciar nova semana? [S/N]" << endl;
        ch=toupper(cin.get());
        cin.ignore();
    }while(ch!='S' && ch!='N');
    system("cls");
    if(ch=='S'){
        cout << "Escolha confirmada: iniciar." << endl << endl;
        aux=entradaDeDadosData();
        dia+=aux.at(0);
        dia+=aux.at(1);
        dint=atoi(dia.c_str());
        mes+=aux.at(3);
        mes+=aux.at(4);
        mint=atoi(mes.c_str());
        for(unsigned int i=0;i<7;i++){
            data[i].m=0;
            data[i].dma=aux;
            dint++;
            dia=to_string(dint);
            mes=to_string(mint);
            if(dint<10) dia='0'+dia;
            if(mint<10) mes='0'+mes;
            aux=dia+'/'+mes+'/'+ano;
            if(mint==2)
                if(dint==28){
                    dint=0;
                    mint++;
                }
            if(mint==4 || mint==6 || mint==9 || mint==11)
                if(dint==30){
                    dint=0;
                    mint++;
                }
            if(dint==31){
                if(mint==12){
                    mint=0;
                    ano="2023";
                }
                dint=0;
                mint++;
            }
        }
        cout << endl << "Agenda inicializada." << endl;
    }
    else cout << "Escolha confirmada: nao iniciar." << endl;
}

void incluiCompromisso(Agenda data[]){
    int posdia,poshinicial,poshfinal;
    bool resp,resp2;
    Agenda auxa;
    Compromisso auxc;
    cout << "INCLUSAO DE COMPROMISSO" << endl;
    auxa.dma=entradaDeDadosData();
    cout << endl << "Data: " << auxa.dma << endl;
    posdia=pesquisaDataERetornaPos(7,data,auxa.dma);
    if(posdia!=-1){
        if(data[posdia].m<6){
            do{
                cout << "Informe a hora inicial (formato: 00:00): ";
                getline(cin,auxc.hinicial);
                resp=validaHora(auxc.hinicial);
                if(!resp) cout << "Dados inconsistentes. Tente novamente." << endl;
            }while(!resp);
            poshinicial=pesquisaHoraERetornaPos(posdia,data,auxc.hinicial,data[posdia].m);
            do{
                cout << "Informe a hora final (formato: 00:00): ";
                getline(cin,auxc.hfinal);
                resp=validaHora(auxc.hfinal);
                resp2=validaHoraInicialxFinal(auxc.hinicial,auxc.hfinal);
                if(!resp || !resp2) cout << "Dados inconsistentes. Tente novamente." << endl;
            }while(!resp || !resp2);
            poshfinal=pesquisaHoraFinalERetornaPos(posdia,data,auxc.hfinal,data[posdia].m);
            if(poshinicial==-1 && poshfinal==-1){
                do{
                    cout << "Informe o tipo: ";
                    getline(cin,auxc.tipo);
                    toUpper(auxc.tipo);
                    resp=verificaSeDifLet(auxc.tipo);
                    resp2=validacaoVazio(auxc.tipo);
                    if(!resp || !resp2) cout << "Dados inconsistentes. Tente novamente." << endl;
                }while(!resp || !resp2);
                do{
                    cout << "Informe o local: ";
                    getline(cin,auxc.local);
                    toUpper(auxc.local);
                    resp=validacaoVazio(auxc.local);
                    if(!resp) cout << "Dados inconsistentes. Tente novamente." << endl;
                }while(!resp);
                do{
                    cout << "Informe o assunto: ";
                    getline(cin,auxc.asst);
                    toUpper(auxc.asst);
                    resp=validacaoVazio(auxc.asst);
                    if(!resp) cout << "Dados inconsistentes. Tente novamente." << endl;
                }while(!resp);

                data[posdia].comp[data[posdia].m]=auxc;
                cout << "Compromisso incluido." << endl;
                data[posdia].m++;
                ordenaComp(data,data[posdia].m,posdia,0,data[posdia].m-1);

            }
            else cout << "Horario ja ocupado." << endl;
        }
        else cout << "Voce ja atingiu o limite de compromissos marcados por dia. Maximo: 6" << endl;
    }
    else cout << "Data nao encontrada." << endl;
}

void excluiCompromisso(Agenda data[]){
    string aux;;
    int posdia, poshora;
    bool resp;

    cout << "EXCLUSAO DE COMPROMISSO" << endl;
    aux=entradaDeDadosData();
    cout << endl << "Data: " << aux << endl;
    posdia=pesquisaDataERetornaPos(7,data,aux);
    if(posdia!=-1){
        do{
            cout << "Informe o horario inicial (formato: 00:00): ";
            getline(cin,aux);
            resp=validaHora(aux);
            if(!resp) cout << "Dados inconsistentes. Tente novamente." << endl;
        }while(!resp);
        poshora=pesquisaHoraERetornaPos(posdia,data,aux,data[posdia].m);
        if(poshora!=-1){
            cout << endl << "Data: " << data[posdia].dma;
            cout << endl << "Horário: " << aux;
            cout << endl << "Excluindo..." << endl;
            data[posdia].comp[poshora]=data[posdia].comp[data[posdia].m-1];
            data[posdia].m--;
            cout << endl << "Compromisso excluido." << endl;
        }
        else cout << "Compromisso inexistente." << endl;
    }
    else cout << "Data nao encontrada." << endl;
}

void relatorio1(Agenda data[]){
    string aux;
    int pos;
    cout << "RELATORIO DIARIO" << endl;
    cout << endl;
    aux=entradaDeDadosData();
    pos=pesquisaDataERetornaPos(7,data,aux);
    system("cls");
    if(pos!=-1){
        if(data[pos].m==0) cout << "Sem compromissos nesta data." << endl;
        else{
            cout << "RELATORIO DIARIO" << endl;
            cout << endl << data[pos].dma << endl;
            cout << data[pos].diasem << endl;
            for(int i=0;i<data[pos].m;i++){
                cout << "Hora inicial: " << data[pos].comp[i].hinicial << endl;
                cout << "Hora final: " << data[pos].comp[i].hfinal << endl;
                cout << "Tipo: " << data[pos].comp[i].tipo << endl;
                cout << "Local: " << data[pos].comp[i].local << endl;
                cout << "Assunto: " << data[pos].comp[i].asst << endl;
            }
        }
    }
    else cout << "Data nao encontrada." << endl;
}

void relatorio2(Agenda data[]){
    cout << "RELATORIO SEMANAL" << endl << endl;
    for(unsigned int i=0;i<7;i++){
        cout << endl << "____" << data[i].dma << "____" << endl;
        cout << data[i].diasem << endl;
        for(int j=0;j<data[i].m;j++){
            cout << endl << "Hora inicial: " << data[i].comp[j].hinicial << endl;
            cout << "Hora final: " << data[i].comp[j].hfinal << endl;
            cout << "Tipo: " << data[i].comp[j].tipo << endl;
            cout << "Local: " << data[i].comp[j].local << endl;
            cout << "Assunto: " << data[i].comp[j].asst << endl;
        }
    }
}
