#include <stdio.h>
#define GT 0.95
#define IMPOSTOS 0.97

int main(){
	float salario_base, novo_salario, base_gt, base_imposto;
	
	printf("Salario base: ");
	scanf("%f", &salario_base);
	
	base_gt = salario_base * GT;
	base_imposto = salario_base * IMPOSTOS;
	
	novo_salario = salario_base + base_gt - base_imposto;  //Salario de 1000; gratificação = 950, impostos = 970, total = 1000 - 970 + 950 = 980
	
	
	printf("Salario liquido: %.2f", novo_salario);
	
	return 0;
}
