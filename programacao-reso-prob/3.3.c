#include <stdio.h>

int main(){
	float a, b, c;
	
	printf("informe o valor do produto A ");
	scanf("%f", &a);
	printf("informe o valor do produto B ");
	scanf("%f", &b);
	printf("informe o valor do produto C ");
	scanf("%f", &c);
	
	if ((a > b) && (a > c))
		printf("O produto A, que custa R$%.2f eh o mais caro", a);
	else if ((b > a) && (b > c))
		printf("O produto B, que custa R$%.2f eh o mais caro", b);	
	else
		printf("O produto C, que custa R$%.2f eh o mais caro", c);
}
