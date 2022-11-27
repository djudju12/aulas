#include <stdio.h>

int main(){
	float altura, comprimento;
	
	printf("Altura do retangulo: ");
	scanf("%f", &altura);
	printf("Comprimento: ");
	scanf("%f", &comprimento);
	
	if (altura == comprimento)
		printf("eh um quadrado!");
	else
		printf("nao eh um quadrado.");

	
	return 0;
}
