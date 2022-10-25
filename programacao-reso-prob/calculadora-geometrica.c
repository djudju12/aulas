#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

void menu();
void comprimento(float raio);
void areaCirculo(float raio);
void areaEsfera(float raio);
void volumeEsfera(float raio);
void areaCilindro(float raio);
void volumeCilindro(float raio);

int main(){
	
	menu();
	
}

void menu(){
	int op;
	float raio;
	
	do{

		printf("----Bem vindo a calculadora geometrica----\n");
		printf("Escolha uma opcao:\n");
		printf("1 - Comprimento da circunferencia\n");
		printf("2 - Area do circulo\n");
		printf("3 - Area da superficie da esfera\n");
		printf("4 - Volume da esfera\n");
		printf("5 - Area da superficie do cilindro\n");
		printf("6 - Volume do cilindro\n");
		printf("7 - Sair\n");
		printf("------------------------------------------\n");
		scanf("%d", &op);
		
		if(op>0 && op<7){
			printf("Raio: ");
			scanf("%f", &raio);
		}
	
		switch(op){
			case 1:
				comprimento(raio);
				break;
			case 2:
				areaCirculo(raio);
				break;
			case 3:
				areaEsfera(raio);
				break;
			case 4:
				volumeEsfera(raio);
				break;
			case 5:
				areaCilindro(raio);
				break;
			case 6:
				volumeCilindro(raio);
				break;
			case 7:
				exit(0);
				break;
			default:
				printf("opcao invalida! ");
		}
		printf("Aperte qualquer tecla para continuar.");
		getch();
		system("cls");
	}while(1);
}

void comprimento(float raio){
	float resultado;
	
	resultado = 2 * M_PI * raio; // 2 * pi * raio
	printf("O comprimento da circunferencia eh: %.2f\n", resultado);
	
}

void areaCirculo(float raio){
	float resultado;
	
	resultado = M_PI * raio * raio; // pi * raio * raio
	printf("A area do circulo eh: %2.f\n", resultado);
}

void areaEsfera(float raio){
	float resultado; 
	
	resultado = 4 * M_PI * raio * raio; //4 * pi * raio * raio
	printf("A area da superficie da esfera eh: %.2f\n", resultado);
	
}

void volumeEsfera(float raio){
	float resultado;
	
	resultado = 4.0/3.0 * M_PI * pow(raio, 3);
	printf("O volume da esfera eh: %.2f\n", resultado);
}

void areaCilindro(float raio){
	float h, resultado;
	
	printf("Informe a altura do cilindro: ");
	scanf("%f", &h);
	resultado = 2 * M_PI * pow(raio, 2) + 2 * M_PI * raio * h;
	printf("A area superificial do cilindro eh: %2.f\n", resultado);
}

void volumeCilindro(float raio){
	float h, resultado;
	
	printf("Informe a altura do cilindro: ");
	scanf("%f", &h);
	resultado = M_PI *pow(raio, 2) * h;
	printf("O volume do cilindro eh: %.2f\n", resultado);
}

