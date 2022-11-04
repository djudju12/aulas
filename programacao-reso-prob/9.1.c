#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 50

void escreverVetor(float vet[], int tamanho);
float somaVetor(float vet[], int tamanho;);
void printVetor(float vet[], int tamanho);
float media(float vet[], int tamanho);
float mediana(float vet[], int tamanho);
float variancia(float vet[], int tamanho);

int main(){
	float vet[MAX], mediaA, medianaA, varianciaA;
	int tamanho, op;
	
	printf("Digite o tamanho do vetor (ateh %d elementos) = ", MAX);
	scanf("%d", &tamanho);
	escreverVetor(vet, tamanho);
	system("cls");
	printf("Vetor:\n");
	printVetor(vet, tamanho);
	printf("<1> Media do vetor\n");
	printf("<2> Mediana do vetor\n");
	printf("<3> Variancia do vetor\n");
	printf("<4> Sair\n");
	do{
		scanf("%d", &op);
		switch(op)
		{
			case 1:
				mediaA = media(vet, tamanho);
				printf("media = %.2f\n", mediaA);
				break;
			case 2:
				medianaA = mediana(vet, tamanho);
				printf("mediana = %.2f\n", medianaA);
				break;
			case 3:
				varianciaA = variancia(vet, tamanho);
				printf("variancia = %.2f\n", varianciaA);
				break;
			case 4:
				exit(0);
				break;
			default:
				printf("Opcao Invalida\n");
		}
	}while(1);
	
	return 0;
}

void escreverVetor(float vet[], int tamanho)
{
	int i;
	
	for(i=0;i<tamanho;i++)
	{
		printf("indice %d = ", i);
		scanf("%f", &vet[i]);
	}
}

float somaVetor(float vet[], int tamanho)
{
	int i;
	float soma=0;
	for(i=0;i<tamanho;i++)
		soma += vet[i];
	
	return soma;
}

void printVetor(float vet[], int tamanho)
{
	int i;
	printf("[");
	for(i=0;i<tamanho;i++)
		printf(" %.2f ", vet[i]);
	printf("]\n");
}

float media(float vet[], int tamanho)
{
	int i;
	float soma = somaVetor(vet, tamanho), media;
	
	media = soma / (float)tamanho;
	return media;
}

float mediana(float vet[], int tamanho)
{
	float mediana;
	if(tamanho%2 == 0)
	{
		mediana = (vet[tamanho/2] + vet[tamanho/2-1])/2.0;
	}
	else
		mediana = vet[tamanho/2];
	return mediana;
}

float variancia(float vet[], int tamanho)
{
	float mediaA, variancia, temp=0;
	int i;
	
	mediaA = media(vet, tamanho);
	for(i=0;i<tamanho;i++)
	{
		temp += pow((vet[i]-mediaA), 2);
	}
	
	variancia = temp/(float)tamanho;
	return variancia;
}
