#include <stdio.h>

int main(){
	float ret, divisor=6, dividendo=3;

	if(divisor=0)
		ret = 0; //se o divisor � zero, n�o posso fazer a divis�o
	else
		ret = dividendo / divisor; //sen�o, posso dividir com seguran�a

	printf("O resultado eh %.2f", ret);
}
