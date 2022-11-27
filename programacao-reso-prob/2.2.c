#include <stdio.h>

int main(){
	float np1, np2, npex, npt, soma, media;
	
	printf("Nota 1: ");
	scanf("%f", &np1);
	printf("Nota 2: ");
	scanf("%f", &np2);
	printf("Nota Trabalho: ");
	scanf("%f", &npt);
	printf("Nota exercicios: ");
	scanf("%f", &npex);
	
	soma = np1 + np2 + npex + npt;
	media = soma / 4; 
	
	if (media >= 7)
		printf("Aluno aprovado com nota %.2f", media);
	else
		printf("Aluno reprovado com nota %.2f", media);	
	
	return 0;
}
