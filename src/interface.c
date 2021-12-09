#include "efolioA.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void menuPrincipal()
{
  int opcao, check, num, ano_lectivo, valorTotalPropina;
  Propinas propina;
  Alunos aluno;

  do{
    //limpa ecran
    clrscr();

    //mostra as opcoes do menu
    printf("\n******************* MENU *******************");
    printf("\n*                                          *");
    printf("\n*   1 - Inserir Dados                      *");
    printf("\n*   2 - Consultar Dados                    *");
    printf("\n*   3 - Alterar Dados                      *");
    printf("\n*   4 - Remover Dados                      *");
    printf("\n*   5 - Calcular Propinas                  *");
    printf("\n*   6 - Reports                            *");
    printf("\n*   0 - Sair                               *");
    printf("\n*                                          *");
    printf("\n********************************************");
    printf("\n\nOpcao: ");
    scanf("%d",&opcao);

    //ver qual eh a opcao
    switch(opcao){
      case 1:
        if(menuInserir()==0)
          opcao=0;
        break;
      case 2:
        if(menuConsultar()==0)
          opcao=0;
        break;
      case 3:
        if(menuAlterar()==0)
          opcao=0;
        break;
      case 4:
        if(menuRemover()==0)
          opcao=0;
        break;
      case 5:
        printf("Numero de aluno: \n");
        scanf("%d",&num);

        //verifica se o aluno existe
        check=Verificar_Aluno(num);
        if(check==-1){
          enter_para_continuar();
          break;
        }else if(check==1){
          printf("Aluno nao existe.\n");
          enter_para_continuar();
          break;
        }else
          printf("Verificado.\n");

        aluno=Consultar_Aluno(num);

        printf("Ano lectivo (ex.: 201819): ");
        scanf("\n%d",&ano_lectivo);

        propina=propinas( num, ano_lectivo);

        if(propina.p==-1){
          printf("\nERRO\n");
          enter_para_continuar();
          break;
        }else if(propina.count==0){
          printf("No ano lectivo seleccionado, o aluno nao esta inscrito a nenhuma UC.\n");
          enter_para_continuar();
          break;
        }else{
          valorTotalPropina=calculoPropinas(aluno,propina);
          imprimeDadosPropina(valorTotalPropina,aluno,propina);
          enter_para_continuar();
          break;
        }

      case 6:
        if(menuReports()==0)
          opcao=0;
        break;

      case 0:
        break;

      default:
        printf("Opcao invalida\n");
        enter_para_continuar();
        break;
      }
  }while(opcao>0);
  printf("\n***************** OBRIGADO *****************\n");
}

int menuInserir()
{
  int opcao, check, num, matriculas, codigo, ano, semestre, ects, ano_letivo;
  char nome[100], pais[50];

  do{
    clrscr();

    printf("\n****************** INSERIR *****************");
    printf("\n*                                          *");
    printf("\n*   1 - Inserir novo Aluno                 *");
    printf("\n*   2 - Inserir nova UC                    *");
    printf("\n*   3 - Inserir nova Inscricao             *");
    printf("\n*                                          *");
    printf("\n*   9 - Voltar ao Menu Anterior            *");
    printf("\n*   0 - Sair                               *");
    printf("\n*                                          *");
    printf("\n********************************************");
    printf("\n\nOpcao: ");
    scanf("%d",&opcao);

    switch(opcao){

      //inserir novo aluno
      case 1:
        printf("Numero de Aluno: ");
        scanf("\n%d",&num);

        //verifica se o aluno existe
        check=Verificar_Aluno(num);
        if(check==-1){
          enter_para_continuar();
          break;
        }else if(check==0){
          printf("Aluno ja existe.\n");
          enter_para_continuar();
          break;
        }else{
          printf("Aluno novo!\n");
        }

        printf("Nome do Aluno: ");
        scanf("\n%[^\n]",nome);
        printf("Pais do Aluno: ");
        scanf("\n%[^\n]",pais);
        printf("Matricula No.: ");
        scanf("\n%d",&matriculas);
        Inserir_Aluno(num,nome,pais,matriculas);
        enter_para_continuar();
        break;

      //inserir nova uc
      case 2:
        printf("Codigo da UC: ");
        scanf("\n%d",&codigo);

        //verifica se a UC existe
        check=Verificar_UC(codigo);
        if(check==-1){
          enter_para_continuar();
          break;
        }else if(check==0){
          printf("UC ja existe.\n");
          enter_para_continuar();
          break;
        }else{
          printf("UC nova!\n");
        }

        printf("Nome da UC: ");
        scanf("\n%[^\n]",nome);
        printf("Ano da UC: ");
        scanf("\n%d",&ano);
        printf("Semestre da UC: ");
        scanf("\n%d",&semestre);
        printf("ECTS da UC: ");
        scanf("\n%d",&ects);
        Inserir_UC(codigo,nome,ano,semestre,ects);
        enter_para_continuar();
        break;

      //inserir nova inscricao
      case 3:
        printf("Numero de Aluno: ");
        scanf("\n%d",&num);

        //verifica se o aluno existe
        check=Verificar_Aluno(num);
        if(check==-1){
          enter_para_continuar();
          break;
        }else if(check==1){
          printf("Aluno nao existe.\n");
          enter_para_continuar();
          break;
        }else{
          printf("Verificado!\n");
        }

        printf("Codigo da UC: ");
        scanf("\n%d",&codigo);

        //verifica se a UC existe
        check=Verificar_UC(codigo);
        if(check==-1){
          enter_para_continuar();
          break;
        }else if(check==1){
          printf("UC nao existe.\n");
          enter_para_continuar();
          break;
        }else{
          printf("Verificado.\n");
        }
        printf("Ano letivo (ex.: 201819): ");
        scanf("\n%d",&ano_letivo);

        //verifica se a inscricao ja existe
        if(Verificar_Inscricao(num,codigo,ano_letivo)==0){
          printf("Inscricao ja existe.\n");
          enter_para_continuar();
          break;
        }

        //verifica se o aluno atingiu o limite de ects
        if(controloECTS(num,codigo,ano_letivo)==-1){
          printf("Inscricao nao possivel. O aluno atingiu o limite de ECTS.\n");
          enter_para_continuar();
          break;
        }

        Inserir_Inscricao(num,codigo,ano_letivo);
        enter_para_continuar();
        break;

      //voltar ao menu anterior
      case 9:
        return 1;

      //sair
      case 0:
        return 0;

      default:
        printf("Opcao invalida\n");
        enter_para_continuar();
        break;
      }
  }while(opcao>0);

  return 1;
}

int menuConsultar()
{
  int opcao, check, num, codigo;
  Alunos aluno;
  UCs uc;

  do{
    clrscr();

    printf("\n***************** CONSULTAR ****************");
    printf("\n*                                          *");
    printf("\n*   1 - Consultar Aluno                    *");
    printf("\n*   2 - Consultar UC                       *");
    printf("\n*   3 - Consultar Inscricoes por Aluno     *");
    printf("\n*   4 - Consultar Inscricoes por UC        *");
    printf("\n*                                          *");
    printf("\n*   9 - Voltar ao Menu Anterior            *");
    printf("\n*   0 - Sair                               *");
    printf("\n*                                          *");
    printf("\n********************************************");
    printf("\n\nOpcao: ");
    scanf("%d",&opcao);

    switch(opcao){

      //consultar aluno
      case 1:
        printf("Numero de aluno: \n");
        scanf("%d",&num);

        //verifica se o aluno existe
        check=Verificar_Aluno(num);
        if(check==-1){
          enter_para_continuar();
          break;
        }else if(check==1){
          printf("Aluno nao existe.\n");
          enter_para_continuar();
          break;
        }

        aluno=Consultar_Aluno(num);
        printf("\n****************** ALUNO *******************");
        printf("\n*   Numero: %d",aluno.numero);
        printf("\n*   Nome: %s",aluno.nome);
        printf("\n*   Pais: %s",aluno.pais);
        printf("\n*   N de Matriculas: %d",aluno.matriculas);
        printf("\n********************************************\n");
        enter_para_continuar();
        break;

      //consultar uc
      case 2:
      printf("Codigo da UC: ");
      scanf("\n%d",&codigo);

      //verifica se a UC existe
      check=Verificar_UC(codigo);
      if(check==-1){
        enter_para_continuar();
        break;
      }else if(check==1){
        printf("UC nao existe.\n");
        enter_para_continuar();
        break;
      }

      uc=Consultar_UC(codigo);
      printf("\n******************** UC ********************");
      printf("\n*   %s",uc.nome);
      printf("\n*   Codigo: %d",uc.codigo);
      printf("\n*   %do ano, %do semestre",uc.ano,uc.semestre);
      printf("\n*   %d ECTS",uc.ects);
      printf("\n********************************************\n");
      enter_para_continuar();
      break;

      //consultar inscricoes por aluno
      case 3:
        printf("Numero de aluno: \n");
        scanf("%d",&num);

        //verifica se o aluno existe
        check=Verificar_Aluno(num);
        if(check==-1){
          enter_para_continuar();
          break;
        }else if(check==1){
          printf("Aluno nao existe.\n");
          enter_para_continuar();
          break;
        }

        Consultar_Inscricoes_por_aluno(num);
        enter_para_continuar();
        break;

      //consultar inscricoes por uc
      case 4:
        printf("Codigo da UC: ");
        scanf("\n%d",&codigo);

        //verifica se a UC existe
        check=Verificar_UC(codigo);
        if(check==-1){
          enter_para_continuar();
          break;
        }else if(check==1){
          printf("UC nao existe.\n");
          enter_para_continuar();
          break;
        }

        Consultar_Inscricoes_por_UC(codigo);
        enter_para_continuar();
        break;

      //voltar ao menu anterior
      case 9:
        return 1;

      //sair
      case 0:
        return 0;

      default:
        printf("Opcao invalida\n");
        enter_para_continuar();
        break;
      }
  }while(opcao>0);

  return 1;
}

int menuAlterar()
{
  int opcao, check, num, codigo, ano_lectivo;

  do{
    clrscr();

    printf("\n***************** ALTERAR ******************");
    printf("\n*                                          *");
    printf("\n*   1 - Alterar Aluno                      *");
    printf("\n*   2 - Alterar UC                         *");
    printf("\n*   3 - Alterar Inscricao                  *");
    printf("\n*                                          *");
    printf("\n*   9 - Voltar ao Menu Anterior            *");
    printf("\n*   0 - Sair                               *");
    printf("\n*                                          *");
    printf("\n********************************************");
    printf("\n\nOpcao: ");
    scanf("%d",&opcao);

    switch(opcao){

      //alterar aluno
      case 1:
        printf("Numero de aluno atual: \n");
        scanf("%d",&num);

        //verifica se o aluno existe
        check=Verificar_Aluno(num);
        if(check==-1){
          enter_para_continuar();
          break;
        }else if(check==1){
          printf("Aluno nao existe.\n");
          enter_para_continuar();
          break;
        }

        if(menuAlterar_aluno(num)==0)
          return 0;
        break;

      //alterar uc
      case 2:
        printf("Codigo da UC atual: ");
        scanf("\n%d",&codigo);

        //verifica se a UC existe
        check=Verificar_UC(codigo);
        if(check==-1){
          enter_para_continuar();
          break;
        }else if(Verificar_UC(codigo)==1){
          printf("UC nao existe.\n");
          enter_para_continuar();
          break;
        }
        if(menuAlterar_uc(codigo)==0)
          return 0;
        break;

      //alterar inscricao
      case 3:
        printf("***** Dados da inscricao *****\n");
        printf("Numero de Aluno: ");
        scanf("\n%d",&num);

        //verifica se o aluno existe
        check=Verificar_Aluno(num);
        if(check==-1){
          enter_para_continuar();
          break;
        }else if(check==1){
          printf("Aluno nao existe.\n");
          enter_para_continuar();
          break;
        }else{
          printf("Verificado.\n");
        }

        printf("Codigo da UC: ");
        scanf("\n%d",&codigo);

        //verifica se a UC existe
        check=Verificar_UC(codigo);
        if(check==-1){
          enter_para_continuar();
          break;
        }else if(check==1){
          printf("UC nao existe.\n");
          enter_para_continuar();
          break;
        }else{
          printf("Verificado.\n");
        }

        printf("Ano Lectivo (ex.: 201819): ");
        scanf("\n%d",&ano_lectivo);

        //verifica se a inscricao existe
        if(Verificar_Inscricao(num,codigo,ano_lectivo)!=0){
          printf("Inscricao nao existe.\n");
          enter_para_continuar();
          break;
        }
        if(menuAlterar_inscricao(num,codigo,ano_lectivo)==0)
          return 0;
        break;

      //voltar ao menu anterior
      case 9:
        return 1;

      //sair
      case 0:
        return 0;

      default:
        printf("Opcao invalida\n");
        enter_para_continuar();
        break;
      }
  }while(opcao>0);

  return 1;
}

int menuRemover()
{
  int opcao, check, num, codigo, ano_letivo;

  do{
    clrscr();

    printf("\n****************** REMOVER *****************");
    printf("\n*                                          *");
    printf("\n*   1 - Remover Aluno                      *");
    printf("\n*   2 - Remover UC                         *");
    printf("\n*   3 - Remover Inscricao                  *");
    printf("\n*                                          *");
    printf("\n*   9 - Voltar ao Menu Anterior            *");
    printf("\n*   0 - Sair                               *");
    printf("\n*                                          *");
    printf("\n********************************************");
    printf("\n\nOpcao: ");
    scanf("%d",&opcao);

    switch(opcao){

      //remover aluno
      case 1:
        printf("Numero de aluno: \n");
        scanf("%d",&num);

        //verifica se o aluno existe
        check=Verificar_Aluno(num);
        if(check==-1){
          enter_para_continuar();
          break;
        }else if(check==1){
          printf("Aluno nao existe.\n");
          enter_para_continuar();
          break;
        }

        Apagar_Aluno(num);
        enter_para_continuar();
        break;

      //remover uc
      case 2:
        printf("Codigo da UC: ");
        scanf("\n%d",&codigo);

        //verifica se a UC existe
        check=Verificar_UC(codigo);
        if(check==-1){
          enter_para_continuar();
          break;
        }else if(check==1){
          printf("UC nao existe.\n");
          enter_para_continuar();
          break;
          }

        Apagar_UC(codigo);
        enter_para_continuar();
        break;

      //remover inscricao
      case 3:
        printf("Numero de Aluno: ");
        scanf("\n%d",&num);

        //verifica se o aluno existe
        check=Verificar_Aluno(num);
        if(check==-1){
          enter_para_continuar();
          break;
        }else if(check==1){
          printf("Aluno nao existe.\n");
          enter_para_continuar();
          break;
        }else{
          printf("Verificado.\n");
        }

        printf("Codigo da UC: ");
        scanf("\n%d",&codigo);

        //verifica se a UC existe
        check=Verificar_UC(codigo);
        if(check==-1){
          enter_para_continuar();
          break;
        }else if(check==1){
          printf("UC nao existe.\n");
          enter_para_continuar();
          break;
        }else{
          printf("Verificado.\n");
        }

        printf("Ano letivo (ex.: 201819): ");
        scanf("\n%d",&ano_letivo);

        //verifica se a inscricao ja existe
        if(Verificar_Inscricao(num,codigo,ano_letivo)!=0){
          printf("Inscricao nao existe.\n");
          enter_para_continuar();
          break;
        }

        Apagar_Inscricao(num,codigo,ano_letivo);
        enter_para_continuar();
        break;

      //voltar ao menu anterior
      case 9:
        return 1;

      //sair
      case 0:
        return 0;

      default:
        printf("Opcao invalida\n");
        enter_para_continuar();
        break;
      }
  }while(opcao>0);

  return 1;
}

int menuAlterar_aluno(int num)
{
  Alunos aluno=Consultar_Aluno(num);
  int opcao, check;
  int num_alt, matricula_alt;
  char nome_alt[100], pais_alt[50];

  do{
    clrscr();

    printf("\n**************** DADOS ALUNO ***************");
    printf("\n*    Numero: %d",num);
    printf("\n*    Nome: %s",aluno.nome);
    printf("\n*    Pais: %s",aluno.pais);
    printf("\n*    Matricula No.: %d",aluno.matriculas);
    printf("\n********************************************");
    printf("\n****************** ALTERAR *****************");
    printf("\n*                                          *");
    printf("\n*   1 - Alterar Numero                     *");
    printf("\n*   2 - Alterar Nome                       *");
    printf("\n*   3 - Alterar Pais                       *");
    printf("\n*   4 - Alterar Matricula                  *");
    printf("\n*                                          *");
    printf("\n*   9 - Voltar ao Menu Anterior            *");
    printf("\n*   0 - Sair                               *");
    printf("\n*                                          *");
    printf("\n********************************************");
    printf("\n\nOpcao: ");
    scanf("%d",&opcao);

    switch(opcao){

      //alterar numero aluno
      case 1:
        printf("Novo Numero de Aluno: ");
        scanf("\n%d",&num_alt);

        //verifica se o aluno ja existe
        check=Verificar_Aluno(num_alt);
        if(check==-1){
          enter_para_continuar();
          break;
        }else if(check==0){
          printf("Aluno ja existe.\n");
          enter_para_continuar();
          break;
        }

        Alterar_Aluno(num,num_alt,aluno.nome,aluno.pais,aluno.matriculas);
        printf("\nAlteracao efetuada.\n");
        enter_para_continuar();
        return 1;

      //alterar nome do aluno
      case 2:
        printf("Novo Nome do Aluno: ");
        scanf("\n%[^\n]",nome_alt);
        Alterar_Aluno(num,num,nome_alt,aluno.pais,aluno.matriculas);
        printf("\nAlteracao efetuada.\n");
        enter_para_continuar();
        return 1;

      //alterar pais do aluno
      case 3:
        printf("Novo Pais do Aluno: ");
        scanf("\n%[^\n]",pais_alt);
        Alterar_Aluno(num,num,aluno.nome,pais_alt,aluno.matriculas);
        printf("\nAlteracao efetuada.\n");
        enter_para_continuar();
        return 1;

      //alterar matricula do aluno
      case 4:
        printf("Novo No. de Matricula: ");
        scanf("\n%d", &matricula_alt);
        Alterar_Aluno(num,num,aluno.nome,aluno.pais,matricula_alt);
        printf("\nAlteracao efetuada.\n");
        enter_para_continuar();
        return 1;

      //voltar ao menu anterior
      case 9:
        return 1;

      //sair
      case 0:
        return 0;

      default:
        printf("Opcao invalida\n");
        enter_para_continuar();
        break;
      }
  }while(opcao>0);

  return 1;
}

int menuAlterar_uc(int codigo)
{
  UCs uc=Consultar_UC(codigo);
  int opcao, check;
  int codigo_alt,ano_alt,semestre_alt,ects_alt;
  char nome_alt[100];

  do{
    clrscr();

    printf("\n***************** DADOS UC *****************");
    printf("\n*    %s",uc.nome);
    printf("\n*    Codigo: %d",uc.codigo);
    printf("\n*    %do ano, %do semestre",uc.ano,uc.semestre);
    printf("\n*    %d ECTS",uc.ects);
    printf("\n********************************************");
    printf("\n***************** ALTERAR ******************");
    printf("\n*                                          *");
    printf("\n*   1 - Alterar Nome                       *");
    printf("\n*   2 - Alterar Codigo                     *");
    printf("\n*   3 - Alterar Ano                        *");
    printf("\n*   4 - Alterar Semestre                   *");
    printf("\n*   5 - Alterar ECTS                       *");
    printf("\n*                                          *");
    printf("\n*   9 - Voltar ao Menu Anterior            *");
    printf("\n*   0 - Sair                               *");
    printf("\n*                                          *");
    printf("\n********************************************");
    printf("\n\nOpcao: ");
    scanf("%d",&opcao);

    switch(opcao){

      //alterar nome da uc
      case 1:
        printf("Novo Nome da UC: ");
        scanf("\n%[^\n]",nome_alt);

        Alterar_UC(codigo,codigo,nome_alt,uc.ano,uc.semestre,uc.ects);
        printf("\nAlteracao efetuada.\n");
        enter_para_continuar();
        return 1;

      //alterar codigo da uc
      case 2:
        printf("Novo Codigo da UC: ");
        scanf("\n%d",&codigo_alt);

        //verifica se a UC ja existe
        check=Verificar_UC(codigo_alt);
        if(check==-1){
          enter_para_continuar();
          break;
        }else if(check==0){
          printf("UC ja existe.\n");
          enter_para_continuar();
          break;
        }

        Alterar_UC(codigo,codigo_alt,uc.nome,uc.ano,uc.semestre,uc.ects);
        printf("\nAlteracao efetuada.\n");
        enter_para_continuar();
        return 1;

      //alterar ano da uc
      case 3:
        printf("Novo Ano da UC: ");
        scanf("\n%d",&ano_alt);
        Alterar_UC(codigo,codigo,uc.nome,ano_alt,uc.semestre,uc.ects);
        printf("\nAlteracao efetuada.\n");
        enter_para_continuar();
        return 1;

      //alterar semestre da uc
      case 4:
        printf("Novo Semestre da UC: ");
        scanf("\n%d",&semestre_alt);
        Alterar_UC(codigo,codigo,uc.nome,uc.ano,semestre_alt,uc.ects);
        printf("\nAlteracao efetuada.\n");
        enter_para_continuar();
        return 1;

      //alterar ects da uc
      case 5:
        printf("Novos ECTS da UC: ");
        scanf("\n%d",&ects_alt);
        Alterar_UC(codigo,codigo,uc.nome,uc.ano,uc.semestre,ects_alt);
        printf("\nAlteracao efetuada.\n");
        enter_para_continuar();
        return 1;

      //voltar ao menu anterior
      case 9:
        return 1;

      //sair
      case 0:
        return 0;

      default:
        printf("Opcao invalida\n");
        enter_para_continuar();
        break;
      }
  }while(opcao>0);

  return 1;
}

int menuAlterar_inscricao(int num, int codigo, int ano_lectivo)
{
  int opcao, check;
  int num_alt,codigo_alt,ano_lectivo_alt;

  do{
    clrscr();

    printf("\n************* DADOS INSCRICAO **************");
    printf("\n*    ALUNO %d",num);
    printf("\n*    UC %d",codigo);
    printf("\n*    Ano Lectivo %d",ano_lectivo);
    printf("\n********************************************");
    printf("\n***************** ALTERAR ******************");
    printf("\n*                                          *");
    printf("\n*   1 - Alterar Numero de Aluno            *");
    printf("\n*   2 - Alterar Codigo da UC               *");
    printf("\n*   3 - Alterar Ano Lectivo                *");
    printf("\n*                                          *");
    printf("\n*   9 - Voltar ao Menu Anterior            *");
    printf("\n*   0 - Sair                               *");
    printf("\n*                                          *");
    printf("\n********************************************");
    printf("\n\nOpcao: ");
    scanf("%d",&opcao);

    switch(opcao){

      //alterar numero aluno da inscricao
      case 1:
        printf("Novo Numero de Aluno: ");
        scanf("\n%d",&num_alt);

        //verifica se o aluno existe
        check=Verificar_Aluno(num_alt);
        if(check==-1){
          enter_para_continuar();
          break;
        }else if(check==1){
          printf("Aluno nao existe.\n");
          enter_para_continuar();
          break;
        }

        //verifica se o aluno atingiu o limite de ects
        if(controloECTS(num_alt,codigo,ano_lectivo)==-1){
          printf("Alteracao nao possivel. Limite de ECTS excedido.\n");
          enter_para_continuar();
          break;
        }

        Alterar_Inscricao(num,codigo,ano_lectivo,num_alt,codigo,ano_lectivo);
        printf("\nAlteracao efetuada.\n");
        enter_para_continuar();
        return 1;

      //alterar codigo UC da inscricao
      case 2:
        printf("Novo Codigo UC: ");
        scanf("\n%d",&codigo_alt);

        //verifica se a UC existe
        check=Verificar_UC(codigo_alt);
        if(check==-1){
          enter_para_continuar();
          break;
        }else if(check==1){
          printf("UC nao existe.\n");
          enter_para_continuar();
          break;
        }

        //verifica se o aluno atingiu o limite de ects
        if(controloECTS(num,codigo_alt,ano_lectivo)==-1){
          printf("Alteracao nao possivel. Limite de ECTS excedido.\n");
          enter_para_continuar();
          break;
        }

        Alterar_Inscricao(num,codigo,ano_lectivo,num,codigo_alt,ano_lectivo);
        printf("\nAlteracao efetuada.\n");
        enter_para_continuar();
        return 1;

      //alterar ano lectivo da inscricao
      case 3:
        printf("Novo Ano Letivo: ");
        scanf("\n%d",&ano_lectivo_alt);

        //verifica se o aluno atingiu o limite de ects
        if(controloECTS(num,codigo,ano_lectivo_alt)==-1){
          printf("Alteracao nao possivel. Limite de ECTS excedido.\n");
          enter_para_continuar();
          break;
        }

        Alterar_Inscricao(num,codigo,ano_lectivo,num,codigo,ano_lectivo_alt);
        printf("\nAlteracao efetuada.\n");
        enter_para_continuar();
        return 1;

      //voltar ao menu anterior
      case 9:
        return 1;

      //sair
      case 0:
        return 0;

      default:
        printf("Opcao invalida\n");
        enter_para_continuar();
        break;
      }
  }while(opcao>0);

  return 1;
}

int menuReports()
{
  int opcao, check, ano_lectivo;

  do{
    clrscr();

    printf("\n***************** REPORTS ******************");
    printf("\n*                                          *");
    printf("\n*   1 - Tutores                            *");
    printf("\n*   2 - Caloiros                           *");
    printf("\n*   3 - Regime                             *");
    printf("\n*   4 - Top 10 Paises                      *");
    printf("\n*                                          *");
    printf("\n*   9 - Voltar ao Menu Anterior            *");
    printf("\n*   0 - Sair                               *");
    printf("\n*                                          *");
    printf("\n********************************************");
    printf("\n\nOpcao: ");
    scanf("%d",&opcao);

    switch(opcao){
      case 1:
        printf("Opcao nao disponivel.\n");
        enter_para_continuar();
        break;

      case 2:
        printf("Opcao nao disponivel.\n");
        enter_para_continuar();
        break;

      case 3:
        printf("Ano lectivo (ex.: 201819): ");
        scanf("\n%d",&ano_lectivo);

        check=reports(ano_lectivo);

        if(check==-1){
          printf("\nERRO\n");
          enter_para_continuar();
          break;
        }

        enter_para_continuar();
        break;

      case 4:
        printf("Opcao nao disponivel.\n");
        enter_para_continuar();
        break;

      //voltar ao menu anterior
      case 9:
        return 1;

      //sair
      case 0:
        return 0;

      default:
        printf("Opcao invalida\n");
        enter_para_continuar();
        break;
      }
    }while(opcao>0);

    return 1;
}

//limpar ecran
void clrscr()
{
  system("@cls||clear");
}

void enter_para_continuar()
{
  char c;
  do {
    printf("\n****** Pressione ENTER para continuar ******\n");
    c=getchar();
    c=getchar();
  } while(c!='\n');
}
