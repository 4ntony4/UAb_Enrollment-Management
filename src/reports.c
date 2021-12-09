#include "efolioA.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 1000
#define TP "Tempo Parcial"
#define TI "Tempo Integral"
#define SI "Situacao Irregular"

//remove uma inscricao duplicada do vector listagem
void removeNum(int d, int i, int listagem[])
{
  int j;
  for(j=d;j<i-1;j++){
    listagem[j]=listagem[j+1];
  }
}

//verifica se o vector listagem tem inscricoes repetidas e corrige-o
int corrigeAIPAL(int i, int listagem[])
{
  int j, d;

  for(j=0;j<i;j++)
  {
    for(d=j+1;d<i;d++)
    {
      if(listagem[d]==listagem[j])
      {
        removeNum(d,i,listagem);
        i--;
        j=0;
      }
    }
  }
  return i;
}

//cria ficheiro com todos os alunos inscritos num dado ano lectivo
void Alunos_Inscritos_por_Ano_Lectivo(int ano_lectivo)
{
  Inscricao inscricao;
  FILE *fp1, *fp2;
  int i=0, j;
  int listagem[MAX];

  fp1 = fopen(DB_INSCR, "r");
  if(fp1 == NULL){
    printf("O ficheiro '%s' nao foi encontrado.\n",DB_INSCR);
  }

  while(!feof(fp1))
  {
    if(feof(fp1))
      break;
    fscanf(fp1, "%d;%d;%d", &inscricao.numero, &inscricao.codigo, &inscricao.ano_lectivo);

    if(inscricao.ano_lectivo == ano_lectivo)
    {
      if(feof(fp1))
        break;
      listagem[i]=inscricao.numero;
      i++;
    }
  }

  fclose(fp1);
  i=corrigeAIPAL(i,listagem);

  //cria ou altera o ficheiro DB_AIPAL
  fp2 = fopen(DB_AIPAL, "w");
  if(fp1 == NULL){
    printf("O ficheiro '%s' nao foi encontrado.\n",DB_AIPAL);
  }
  for(j=0;j<i;j++)
  {
    fprintf(fp2, "%d\n", listagem[j]);
  }
  fclose(fp2);
}

//calcula regime de um dado aluno
int regime(int total_ects)
{
  if(total_ects>=6&&total_ects<=60){
    //tempo parcial
    return 1;
  }else if(total_ects>60){
    //tempo integral
    return 2;
  }else{
    //situacao irregular
    return 3;
  }
}

int imprimeReport(int ano_lectivo,int countTP,int countTI,int countSI)
{
  int num, total_ects;
  char regime[100];
  FILE *fp;

  fp = fopen(DB_REPORT, "r");
  if(fp == NULL){
    printf("O Ficheiro '%s' nao foi encontrado.\n", DB_REPORT);
		return -1;
	}
  printf("\n");

	while(!feof(fp)){
    fscanf(fp, "%d;%d;%[^\n]", &num, &total_ects, regime);
    if(feof(fp))
      break;
    printf("%10d, %2d ECTS, %s\n",num,total_ects,regime);
  }
  fclose(fp);


  printf("\nNo ano lectivo %d existem %d aluno(s) inscritos dos quais:\n", ano_lectivo, countTI+countTP+countSI);
  printf("%3d a %s\n",countTP,TP);
  printf("%3d a %s\n",countTI,TI);
  printf("%3d em %s\n",countSI,SI);

  return 0;
}

int reports(int ano_lectivo)
{
  int check, t_regime, num, countTP=0, countTI=0, countSI=0;
  Propinas propina;
  FILE *fp1, *fp2;

  Alunos_Inscritos_por_Ano_Lectivo(ano_lectivo);

  fp1 = fopen(DB_AIPAL, "r");
  if(fp1 == NULL){
    printf("O Ficheiro '%s' nao foi encontrado.\n", DB_AIPAL);
    return -1;
  }
  fp2 = fopen(DB_REPORT, "w");
  if(fp2 == NULL){
    printf("O Ficheiro '%s' nao foi encontrado.\n", DB_REPORT);
    return -1;
  }

  while(!feof(fp1)){
    fscanf(fp1, "%d", &num);

    //obter total de ects de um dado aluno
    propina=propinas(num,ano_lectivo);

    //calcular regime
    t_regime=regime(propina.total_ects);

    if(feof(fp1))
      break;

    if(t_regime==1){
      fprintf(fp2, "%d;%d;%s\n", num, propina.total_ects, TP);
      countTP++;
    }else if(t_regime==2){
      fprintf(fp2, "%d;%d;%s\n", num, propina.total_ects, TI);
      countTI++;
    }else{
      fprintf(fp2, "%d;%d;%s\n", num, propina.total_ects, SI);
      countSI++;
    }
  }

  fclose(fp1);
  fclose(fp2);
  remove(DB_AIPAL);

  check=imprimeReport(ano_lectivo,countTP,countTI,countSI);

  if(check==-1){
    return -1;
  }

  return 0;
}
