#include <stdio.h>

int main(){
	float salario, aumento, novo_salario;
	
	printf("Digite o salario: ");
	scanf("%f", &salario);
	printf("Digite o aumento em decimal: ");
	scanf("%f", &aumento);
	
	novo_salario = salario * aumento;
	
	printf("o salario com aumento de %f eh = %f", aumento, novo_salario);	
	
	return 0;
}
