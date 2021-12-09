#include "efolioA.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Propinas propinas(int num, int ano_lectivo)
{
  UCs uc;
  Inscricao inscricao;
  Propinas propina={0,0,0};
  FILE *fp1, *fp2;

  //consulta e conta o numero de inscricoes num ano letivo especifico e calcula o total de ects inscritos
  fp1 = fopen(DB_INSCR, "r");
  if(fp1 == NULL){
		printf("O Ficheiro '%s' nao foi encontrado.\n", DB_INSCR);
    propina.p=-1;
    return propina;
	}
	fp2 = fopen(DB_PROPINAS, "w");
	if(fp2 == NULL){
		printf("O Ficheiro '%s' nao foi encontrado.\n", DB_PROPINAS);
    propina.p=-1;
    return propina;
	}
  while(!feof(fp1))
	{
		if(feof(fp1))
			break;
		fscanf(fp1, "%d;%d;%d", &inscricao.numero, &inscricao.codigo, &inscricao.ano_lectivo);
    if(inscricao.numero == num && inscricao.ano_lectivo == ano_lectivo)
		{
			if(feof(fp1))
				break;
			propina.count++;
      uc=Consultar_UC(inscricao.codigo);
      propina.total_ects+=uc.ects;
			fprintf(fp2,"%d;%d;%d\n",inscricao.numero,inscricao.codigo,inscricao.ano_lectivo);
		}
	}

	fclose(fp1);
	fclose(fp2);
  remove(DB_PROPINAS);

  return propina;
}

int calculoPropinas(Alunos aluno, Propinas propina)
{
  int valorMatricula;

  //calcular o valor da matricula
  if(aluno.matriculas==1&&strcmp(aluno.pais, "Portugal") == 0){
    valorMatricula=80;
  }else if(aluno.matriculas==1&&strcmp(aluno.pais, "Portugal") != 0){
    valorMatricula=96;
  }else{
    valorMatricula=0;
  }

  //calcular o valor total da propina
  if(strcmp(aluno.pais, "Portugal") == 0){
    return (propina.total_ects*15)+valorMatricula;
  }else{
    return (propina.total_ects*18)+valorMatricula;
  }
}

void imprimeDadosPropina(int valorTotalPropina, Alunos aluno, Propinas propina)
{
  if(strcmp(aluno.pais, "Portugal") == 0){

    printf("Aluno residente em Portugal.\n");

    //ver se eh 1o ano ou nao
    if(aluno.matriculas==1){
      printf("1o Ano (Inclui taxa de Matricula).\n");
    }else{
      printf("Sem taxa de Matricula.\n");
    }

    printf("Inscrito em %d ECTS (%d UCs).\n", propina.total_ects, propina.count);
    printf("Valor Total da Propina: %d eur.\n",valorTotalPropina);
  }else{

    printf("Aluno residente no estrangeiro.\n");

    //ver se eh 1o ano ou nao
    if(aluno.matriculas==1){
      printf("1o Ano (Inclui taxa de Matricula).\n");
    }else{
      printf("Sem taxa de Matricula.\n");
    }

    printf("Inscrito em %d ECTS (%d UCs).\n", propina.total_ects, propina.count);
    printf("Valor Total da Propina: %d eur.\n",valorTotalPropina);
  }
}

int controloECTS(int num, int codigo, int ano_lectivo)
{
  int maxECTS;
  Alunos aluno;
  UCs uc;
  Propinas propina;

  aluno=Consultar_Aluno(num);
  uc=Consultar_UC(codigo);
  propina=propinas( num, ano_lectivo);

  if(aluno.matriculas==1){
    maxECTS=60;
  }else{
    maxECTS=84;
  }

  if(propina.total_ects+uc.ects>maxECTS){
    return -1;
  }

  return 0;
}
