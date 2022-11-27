#include <stdio.h>

int main()
{
	float salario, novo_salario;
	
	printf("Digite seu salario: ");
	scanf("%f", &salario);
	
	novo_salario = salario * 0.80;
	
	printf("Seu salario com 20%% de desconto eh: %.2f", novo_salario);
	
    return 0;
}
