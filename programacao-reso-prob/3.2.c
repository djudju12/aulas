#include <stdio.h>

int main(){
	int num1, num2, soma;
	
	printf("digite o numero 1: ");
	scanf("%d", &num1);
	printf("digite o numero 2: ");
	scanf("%d", &num2);
	
	if ((num1 % 2 == 0) && (num2 % 2 == 0))
		printf("%d", (num1 + num2));
	else
		printf("%d", (num1*num2));
	
	
	return 0;
}
