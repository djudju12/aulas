#include <stdio.h>

int main(){
	int ano_nasc, ano_atual;
	
	printf("Ano atual: ");
	scanf("%d", &ano_atual);
	printf("Ano de nascimento: ");
	scanf("%d", &ano_nasc);
	
	printf("Idade atual = %d\n", (ano_atual - ano_nasc));
	printf("Em 2030 tera %d anos", (2030 - ano_nasc));
	
	return 0;
}
