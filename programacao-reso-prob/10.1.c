#include <stdio.h>
#define MAX 50
#define NOTAS 4

void entradaDados(int alunos, float notas[][NOTAS]);
float calcularMedia(int aluno, float notas[][NOTAS]);

int main(){
	float notas[MAX][NOTAS], media;
	int alunos, i;
	
	printf("Quantidade de alunos? ");
	scanf("%d", &alunos);
	entradaDados(alunos, notas);
	
	for(i=0;i<alunos;i++){
		media = calcularMedia(i, notas);
		printf("Media do aluno %d = %.2f\n", i+1, media);
	}
	
	return 0;
}

float calcularMedia(int aluno, float notas[][NOTAS]){
	int i;
	float media, soma;
	
	soma=0;
	for(i=0;i<NOTAS;i++)
		soma += notas[aluno][i];
	
	media = soma/NOTAS;
	return media;
}

void entradaDados(int alunos, float notas[][NOTAS]){
	int i, j;
	
	for(i=0;i<alunos;i++){
		for(j=0;j<NOTAS;j++){
			printf("Digite a nota %d do aluno %d: ", j+1, i+1);
			scanf("%f", &notas[i][j]);
		}
	}
}
