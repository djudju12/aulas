#include <stdio.h>

int main(){
	float ret, divisor=6, dividendo=3;

	if(divisor=0)
		ret = 0; //se o divisor é zero, não posso fazer a divisão
	else
		ret = dividendo / divisor; //senão, posso dividir com segurança

	printf("O resultado eh %.2f", ret);
}
