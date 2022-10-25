/*6.2. Finalize o seguinte programa, inclusive desenvolvendo os
códigos necessários para que ele realize todos os cálculos
propostos.*/
#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <stdlib.h>
#define PI 3.14

int main()
{
	int op, ch=1;
	float raio, resultado, h, temp;
	
	while ch==1:	
		printf("----Bem vindo a calculadora geometrica----\n");
		printf("Escolha uma opcao:\n");
		printf("1 - Comprimento da circunferencia\n");
		printf("2 - Area do circulo\n");
		printf("3 - Area da superficie da esfera\n");
		printf("4 - Volume da esfera\n");
		printf("5 - Area da superficie do cilindro\n");
		printf("6 - Volume do cilindro\n");
		printf("------------------------------------------\n");
		scanf("%d", &op);
		printf("Informe o raio: ");
		scanf("%f", &raio);
		
		switch(op){
			case 1:
				resultado = 2 * PI * raio; // 2 * pi * raio
				printf("O comprimento da circunferencia eh: %.2f\n", resultado);
				break;
			case 2:
				resultado = PI * raio * raio; // pi * raio * raio
				printf("A area do circulo eh: %2.f\n", resultado);
				break;
			case 3:
				resultado = 4 * PI * raio * raio; //4 * pi * raio * raio
				printf("A area da superficie da esfera eh: %.2f\n", resultado);
				break;
			case 4:
				resultado = 4/3 * PI * pow(raio, 3);
				printf("O volume da esfera eh: %.2f\n", resultado);
				break;
			case 5:
				printf("Informe a altura do cilindro: ");
				scanf("%f", &h);
				resultado = 2 * PI * raio * raio + 2 * PI * raio * h;
				printf("A area superificial do cilindro eh: %2.f\n", resultado);
				break;
			case 6:
				printf("Informe a altura do cilindro: ");
				scanf("%f", &h);
				temp = PI * raio * raio;
				resultado = temp * h;
				printf("O volume do cilindro eh: %.2f\n", resultado);
				break;
			default:
				printf("Operacao invalida!\n");
				break;
		}
		
		printf("\n1-Fazer outra operacao\n2-Sair\n");
		scanf("%d", ch);
		
		if (ch)
		{
			printf("1");
			goto operacao;
		}
		
			
	return 0;
}
