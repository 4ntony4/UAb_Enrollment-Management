#ifndef EFOLIO_A_H
#define EFOLIO_A_H

#define DB_ALUNO       "db/DtBs_Alunos.dat"
#define DB_ALUNO_TEMP  "db/DtBs_Alunos_Temp.dat"
#define DB_UC          "db/DtBs_UCs.dat"
#define DB_UC_TEMP     "db/DtBs_UCs_Temp.dat"
#define DB_INSCR       "db/DtBs_Inscricoes.dat"
#define DB_INSCR_TEMP  "db/DtBs_Inscricoes_Temp.dat"
#define DB_PROPINAS    "db/DtBs_Propinas.dat"
#define DB_AIPAL       "db/DtBs_Alunos_Inscritos_por_Ano_Lectivo.dat"
#define DB_REPORT      "db/DtBs_Report.dat"

//----- ESTRUTURAS -----
typedef struct Alunos
{
    int numero;
    char nome[100];
    char pais[50];
    int matriculas;
} Alunos;

typedef struct UCs
{
    int codigo;
    char nome[100];
    int ano;
    int semestre;
    int ects;
} UCs;

typedef struct Inscricao
{
    int numero;
    int codigo;
    int ano_lectivo;
} Inscricao;

typedef struct Propinas
{
    int p;  //variavel de controlo
    int count;
    int total_ects;
} Propinas;

//----- VERIFICAR DADOS -----
int Verificar_Aluno(int);
int Verificar_UC(int);
int Verificar_Inscricao(int,int,int);

//----- CONSULTAR DADOS -----
Alunos Consultar_Aluno(int);
UCs Consultar_UC(int);
void Consultar_Inscricoes_por_aluno(int);
void Consultar_Inscricoes_por_UC(int);

//----- INSERIR DADOS -----
void Inserir_Aluno(int,char*,char*,int);
void Inserir_UC(int,char*,int,int,int);
void Inserir_Inscricao(int,int,int);

//----- APAGAR DADOS -----
void Apagar_Aluno(int);
void Apagar_UC(int);
void Apagar_Inscricao(int,int,int);

//----- ALTERAR DADOS -----
void Alterar_Aluno(int,int,char*,char*,int);
void Alterar_UC(int,int,char*,int,int,int);
void Alterar_Inscricao(int,int,int,int,int,int);

//----- INTERFACE -----
void menuPrincipal();
int menuInserir();
int menuConsultar();
int menuAlterar();
int menuRemover();
int menuAlterar_aluno(int);
int menuAlterar_uc(int);
int menuAlterar_inscricao(int,int,int);
int menuReports();

//----- LIMPAR ECRAN -----
void clrscr();
void enter_para_continuar();

//----- CONTROLO -----
Propinas propinas(int,int);
int calculoPropinas(Alunos,Propinas);
void imprimeDadosPropina(int,Alunos,Propinas);
int controloECTS(int,int,int);

//----- REPORTS -----
void removeNum(int,int,int*);
int corrigeAIPAL(int,int*);
void Alunos_Inscritos_por_Ano_Lectivo(int);
int regime(int);
int imprimeReport(int,int,int,int);
int reports(int);

#endif //EFOLIO_A_H
