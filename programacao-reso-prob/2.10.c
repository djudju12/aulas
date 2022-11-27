#include <stdio.h>

int main(){
	int ano_nasc, ano_atual;
	
	printf("Ano atual: ");
	scanf("%d", &ano_atual);
	printf("Ano de nascimento: ");
	scanf("%d", &ano_nasc);
	
	printf("Idade %d anos\n", (ano_atual - ano_nasc));
	printf("%d meses\n", ((ano_atual - ano_nasc)*12));
	printf("%d dias\n", (((ano_atual - ano_nasc)*12*30)));
	printf("%d dias\n", ((((ano_atual - ano_nasc)*12*30)*7)));
	
	return 0;
}
