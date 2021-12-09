#include "efolioA.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//----- VERIFICAR DADOS -----
int Verificar_Aluno(int num)
{
	Alunos aluno;

  FILE *fp;
  fp = fopen(DB_ALUNO, "r");
  if(fp == NULL){
    printf("O Ficheiro '%s' nao foi encontrado.\n", DB_ALUNO);
		return -1;
	}

	while(!feof(fp)){
    fscanf(fp, "%d;%[^;];%[^;];%d", &aluno.numero, aluno.nome, aluno.pais, &aluno.matriculas);
    if(aluno.numero == num){
			fclose(fp);
      return 0;
		}
	}
  fclose(fp);
	return 1;
}
int Verificar_UC(int num)
{
	UCs uc;

  FILE *fp;
  fp = fopen(DB_UC, "r");
  if(fp == NULL){
    printf("O Ficheiro '%s' nao foi encontrado.\n", DB_UC);
		return -1;
	}

	while(!feof(fp)){
		fscanf(fp, "%d;%[^;];%d;%d;%d", &uc.codigo, uc.nome, &uc.ano, &uc.semestre, &uc.ects);
    if(uc.codigo == num){
			fclose(fp);
      return 0;
		}
	}

  fclose(fp);
	return 1;
}
int Verificar_Inscricao(int num, int codigo, int ano_lectivo)
{
	Inscricao inscricao;

  FILE *fp;
  fp = fopen(DB_INSCR, "r");
  if(fp == NULL){
    printf("O Ficheiro '%s' nao foi encontrado.\n", DB_INSCR);
		return -1;
	}

	while(!feof(fp)){
    fscanf(fp, "%d;%d;%d", &inscricao.numero, &inscricao.codigo, &inscricao.ano_lectivo);
    if(inscricao.numero == num && inscricao.codigo == codigo && inscricao.ano_lectivo == ano_lectivo){
			fclose(fp);
      return 0;
		}
	}

  fclose(fp);
	return 1;
}

//----- CONSULTAR DADOS -----
Alunos Consultar_Aluno(int num)
{
	Alunos aluno, aux={0};

  FILE *fp;
  fp = fopen(DB_ALUNO, "r");
  if(fp == NULL){
    printf("O Ficheiro '%s' nao foi encontrado.\n", DB_ALUNO);
		return aux;
	}

  //Procura no ficheiro pelo dado entrado
	while(!feof(fp))
	{
		fscanf(fp, "%d;%[^;];%[^;];%d", &aluno.numero, aluno.nome, aluno.pais, &aluno.matriculas);
    if(aluno.numero == num)
		{
			fclose(fp);
			return aluno;
		}
	}

  fclose(fp);
	return aux;
}
UCs Consultar_UC(int num)
{
	UCs uc, aux={0};

  FILE *fp;
  fp = fopen(DB_UC, "r");
  if(fp == NULL){
    printf("O Ficheiro '%s' nao foi encontrado.\n", DB_UC);
		return aux;
	}

  //Procura no ficheiro pelo dado entrado
	while(!feof(fp))
	{
		fscanf(fp, "%d;%[^;];%d;%d;%d", &uc.codigo, uc.nome, &uc.ano, &uc.semestre, &uc.ects);
    if(uc.codigo == num)
		{
			fclose(fp);
			return uc;
		}
	}
  fclose(fp);
	return aux;
}
void Consultar_Inscricoes_por_aluno(int num)
{
	Inscricao inscricao;
	int count=0;

  FILE *fp1, *fp2;
  fp1 = fopen(DB_INSCR, "r");
  if(fp1 == NULL){
		printf("O Ficheiro '%s' nao foi encontrado.\n", DB_INSCR);
	}
	fp2 = fopen(DB_INSCR_TEMP, "w");
	if(fp2 == NULL){
		printf("O Ficheiro '%s' nao foi encontrado.\n", DB_INSCR);
	}

	while(!feof(fp1))
	{
		if(feof(fp1))
			break;
		fscanf(fp1, "%d;%d;%d", &inscricao.numero, &inscricao.codigo, &inscricao.ano_lectivo);
    if(inscricao.numero == num)
		{
			if(feof(fp1))
				break;
			count++;
			fprintf(fp2,"%d;%d;%d\n",inscricao.numero,inscricao.codigo,inscricao.ano_lectivo);
		}
	}
	fclose(fp1);
	fclose(fp2);

	//Imprime consulta
	if(count==0){
		printf("\nO aluno nao esta inscrito em nenhuma UC.\n");
	}else{
		fp2 = fopen(DB_INSCR_TEMP, "r");
		if(fp2 == NULL){
			printf("O Ficheiro '%s' nao foi encontrado.\n", DB_INSCR);
		}

		printf("\nO aluno esta inscrito em %d UC(s):\n",count);
		while(!feof(fp2)){
			fscanf(fp2, "%d;%d;%d", &inscricao.numero, &inscricao.codigo, &inscricao.ano_lectivo);
			if(feof(fp2))
				break;
			fprintf(stdout,"   %d, %d\n",inscricao.codigo,inscricao.ano_lectivo);
		}
		fclose(fp2);
	}
	remove(DB_INSCR_TEMP);
}
void Consultar_Inscricoes_por_UC(int codigo)
{
	Inscricao inscricao;
	int count=0;

  FILE *fp1, *fp2;
  fp1 = fopen(DB_INSCR, "r");
  if(fp1 == NULL){
    printf("O Ficheiro '%s' nao foi encontrado.\n", DB_INSCR);
	}
	fp2 = fopen(DB_INSCR_TEMP, "w");
	if(fp2 == NULL){
		printf("O Ficheiro '%s' nao foi encontrado.\n", DB_INSCR);
	}
	while(!feof(fp1))
	{
		fscanf(fp1, "%d;%d;%d", &inscricao.numero, &inscricao.codigo, &inscricao.ano_lectivo);
    if(inscricao.codigo == codigo)
		{
			if(feof(fp1))
				break;
			count++;
			fprintf(fp2,"%d;%d;%d\n",inscricao.numero,inscricao.codigo,inscricao.ano_lectivo);
		}
	}
	fclose(fp1);
	fclose(fp2);

	//imprime consulta
	if(count==0){
		printf("\nA UC nao tem alunos...\n");
	}else{
		fp2 = fopen(DB_INSCR_TEMP, "r");
		if(fp2 == NULL){
			printf("O Ficheiro '%s' nao foi encontrado.\n", DB_INSCR);
		}
		printf("\nA UC tem %d aluno(s):\n",count);
		while(!feof(fp2)){
				fscanf(fp2, "%d;%d;%d", &inscricao.numero, &inscricao.codigo, &inscricao.ano_lectivo);
				if(feof(fp2))
					break;
				fprintf(stdout,"   %d, %d\n",inscricao.numero,inscricao.ano_lectivo);
			}
		fclose(fp2);
	}
	remove(DB_INSCR_TEMP);
}

//----- INSERIR DADOS -----
void Inserir_Aluno(int num, char nome[100], char pais[50], int matriculas)
{
  FILE *fp;
  fp = fopen(DB_ALUNO, "a");
  if(fp == NULL){
    printf("O Ficheiro '%s' nao foi encontrado.\n", DB_ALUNO);
	}
  fprintf(fp, "%d;%s;%s;%d\n", num, nome, pais, matriculas);
  printf("\nAluno criado!\n");

  fclose(fp);
}
void Inserir_UC(int num, char nome[100], int ano, int semestre, int ects)
{
  FILE *fp;
  fp = fopen(DB_UC, "a");
  if(fp == NULL){
    printf("O Ficheiro '%s' nao foi encontrado.\n", DB_UC);
	}

  fprintf(fp, "%d;%s;%d;%d;%d\n", num, nome, ano, semestre, ects);
  printf("\nUC criada!\n");

  fclose(fp);
}
void Inserir_Inscricao(int num, int codigo, int ano_lectivo)
{
  FILE *fp;
  fp = fopen(DB_INSCR, "a");
  if(fp == NULL){
  	printf("O Ficheiro '%s' nao foi encontrado.\n", DB_INSCR);
	}

  fprintf(fp, "%d;%d;%d\n", num, codigo, ano_lectivo);
  printf("\nInscricao criada!\n");

  fclose(fp);
}

//----- APAGAR DADOS -----
void Apagar_Aluno(int num)
{
  Alunos aluno;

  FILE *fp1, *fp2;
  fp1 = fopen(DB_ALUNO, "r");
  if(fp1 == NULL){
    printf("O Ficheiro '%s' nao foi encontrado.\n", DB_ALUNO);
	}
  fp2 = fopen(DB_ALUNO_TEMP, "w");
  if(fp2 == NULL){
    printf("O Ficheiro '%s' nao foi encontrado.\n", DB_ALUNO_TEMP);
	}

	while(!feof(fp1))
	{
		if(feof(fp1))
			break;
		fscanf(fp1, "%d;%[^;];%[^;];%d", &aluno.numero, aluno.nome, aluno.pais, &aluno.matriculas);
    if(aluno.numero != num)
		{
			if(feof(fp1))
				break;
	    fprintf(fp2, "%d;%s;%s;%d\n", aluno.numero, aluno.nome, aluno.pais, aluno.matriculas);
    }
	}
	printf("\nAluno removido!\n");
  fclose(fp1);
  fclose(fp2);
  remove(DB_ALUNO);
  rename(DB_ALUNO_TEMP,DB_ALUNO);
}
void Apagar_UC(int codigo)
{
	UCs UCs;

	FILE *fp1, *fp2;
	fp1 = fopen(DB_UC, "r");
	if(fp1 == NULL){
		printf("O Ficheiro '%s' nao foi encontrado.\n", DB_UC);
	}
	fp2 = fopen(DB_UC_TEMP, "w");
	if(fp2 == NULL){
		printf("O Ficheiro '%s' nao foi encontrado.\n", DB_UC_TEMP);
	}

	while(!feof(fp1))
	{
		fscanf(fp1, "%d;%[^;];%d;%d;%d", &UCs.codigo, UCs.nome, &UCs.ano, &UCs.semestre, &UCs.ects);
	  if(UCs.codigo != codigo)
		{
			if(feof(fp1))
				break;
	    fprintf(fp2, "%d;%s;%d;%d;%d\n", UCs.codigo, UCs.nome, UCs.ano, UCs.semestre, UCs.ects);
		}
	}
	printf("\nUC removida!\n");
	fclose(fp1);
	fclose(fp2);
	remove(DB_UC);
	rename(DB_UC_TEMP,DB_UC);
}
void Apagar_Inscricao(int num, int codigo, int ano_lectivo)
{
  Inscricao Inscricao;

  FILE *fp1, *fp2;
  fp1 = fopen(DB_INSCR, "r");
  if(fp1 == NULL){
  	printf("O Ficheiro '%s' nao foi encontrado.\n", DB_INSCR);
	}
  fp2 = fopen(DB_INSCR_TEMP, "w");
  if(fp2 == NULL){
    printf("O Ficheiro '%s' nao foi encontrado.\n", DB_INSCR_TEMP);
	}

	while(!feof(fp1))
	{
		fscanf(fp1, "%d;%d;%d", &Inscricao.numero, &Inscricao.codigo, &Inscricao.ano_lectivo);
  	if(Inscricao.numero == num && Inscricao.codigo == codigo && Inscricao.ano_lectivo == ano_lectivo)
		{
			if(feof(fp1))
				break;
		}
		else
		{
			if(feof(fp1))
				break;
			fprintf(fp2, "%d;%d;%d\n", Inscricao.numero, Inscricao.codigo, Inscricao.ano_lectivo);
    }
	}

	printf("\nInscricao removida!\n");
  fclose(fp1);
  fclose(fp2);
  remove(DB_INSCR);
  rename(DB_INSCR_TEMP,DB_INSCR);
}

//----- ALTERAR DADOS -----
void Alterar_Aluno(int num, int num_alt, char nome_alt[100], char pais_alt[50], int matriculas_alt)
{
  Alunos aluno;

  FILE *fp1, *fp2;
  fp1 = fopen(DB_ALUNO, "r");
  if(fp1 == NULL){
    printf("O Ficheiro '%s' nao foi encontrado.\n", DB_ALUNO);
	}
  fp2 = fopen(DB_ALUNO_TEMP, "w");
  if(fp2 == NULL){
		printf("O Ficheiro '%s' nao foi encontrado.\n", DB_ALUNO_TEMP);
	}

	while(!feof(fp1))
	{
		if(feof(fp1))
			break;
		fscanf(fp1, "%d;%[^;];%[^;];%d", &aluno.numero, aluno.nome, aluno.pais, &aluno.matriculas);
		if(aluno.numero == num){
			if(feof(fp1))
				break;
			fprintf(fp2, "%d;%s;%s;%d\n", num_alt, nome_alt, pais_alt, matriculas_alt);
		}else{
			if(feof(fp1))
				break;
			fprintf(fp2, "%d;%s;%s;%d\n", aluno.numero, aluno.nome, aluno.pais ,aluno.matriculas);
		}
	}
  fclose(fp1);
  fclose(fp2);
  remove(DB_ALUNO);
  rename(DB_ALUNO_TEMP,DB_ALUNO);
}
void Alterar_UC(int codigo, int codigo_alt, char nome_alt[100], int ano_alt,int semestre_alt, int ects_alt)
{
  UCs uc;

  FILE *fp1, *fp2;
  fp1 = fopen(DB_UC, "r");
  if(fp1 == NULL){
		printf("O Ficheiro '%s' nao foi encontrado.\n", DB_UC);
	}
  fp2 = fopen(DB_UC_TEMP, "w");
  if(fp2 == NULL){
    printf("O Ficheiro '%s' nao foi encontrado.\n", DB_UC_TEMP);
	}

	while(!feof(fp1)){
		if(feof(fp1))
			break;
		fscanf(fp1, "%d;%[^;];%d;%d;%d", &uc.codigo, uc.nome, &uc.ano, &uc.semestre, &uc.ects);
		if(uc.codigo != codigo)
		{
			if(feof(fp1))
				break;
	    fprintf(fp2, "%d;%s;%d;%d;%d\n", uc.codigo, uc.nome, uc.ano, uc.semestre, uc.ects);
    }else{
			if(feof(fp1))
				break;
      fprintf(fp2, "%d;%s;%d;%d;%d\n", codigo_alt, nome_alt, ano_alt, semestre_alt, ects_alt);
		}
	}

  fclose(fp1);
  fclose(fp2);
  remove(DB_UC);
  rename(DB_UC_TEMP,DB_UC);
}
void Alterar_Inscricao(int num, int codigo, int ano_lectivo, int num_alt, int codigo_alt, int ano_lectivo_alt)
{
  Inscricao inscricao;

  FILE *fp1, *fp2;
  fp1 = fopen(DB_INSCR, "r");
  if(fp1 == NULL){
    printf("O Ficheiro '%s' nao foi encontrado.\n", DB_INSCR);
	}
  fp2 = fopen(DB_INSCR_TEMP, "w");
  if(fp2 == NULL){
    printf("O Ficheiro '%s' nao foi encontrado.\n", DB_INSCR_TEMP);
	}

	while(!feof(fp1))
	{
		fscanf(fp1, "%d;%d;%d", &inscricao.numero, &inscricao.codigo, &inscricao.ano_lectivo);

		if(inscricao.numero == num && inscricao.codigo == codigo && inscricao.ano_lectivo == ano_lectivo)
		{
			if(feof(fp1))
				break;
			fprintf(fp2, "%d;%d;%d\n", num_alt, codigo_alt, ano_lectivo_alt);
    }else{
			if(feof(fp1))
				break;
			fprintf(fp2, "%d;%d;%d\n", inscricao.numero, inscricao.codigo, inscricao.ano_lectivo);
		}
	}

  fclose(fp1);
  fclose(fp2);
  remove(DB_INSCR);
  rename(DB_INSCR_TEMP,DB_INSCR);
}
