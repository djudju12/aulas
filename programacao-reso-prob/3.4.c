#include <stdio.h>

int main(){
	char item[20];
	int cod, qnt;
	
	printf("digite o codigo do produto: ");
	scanf("%d", &cod);
	printf("digite a quantidade: ");
	scanf("%d", &qnt);
	
	switch(cod){
		case 100:
			printf("%d Cachorro Quente valor: R$%.2f", qnt, (qnt * 1.20));
			break;
		case 101:
			printf("%d Bauro Simples valor: R$%.2f", qnt, (qnt * 1.30));
			break;
		case 102:
			printf("%d Bauro Ovo valor: R$%.2f", qnt, (qnt * 1.50));
			break;
		case 103:
			printf("%d Hamburguer valor: R$%.2f", qnt, (qnt * 1.20));
			break;
		case 104:
			printf("%d Cheeseburguer valor: R$%.2f", qnt, (qnt * 1.30));
			break;
		case 105:
			printf("%d Refrigerante valor: R$%.2f", qnt, (qnt * 1.00));
			break;
		default:
			printf("Codigo incorreto");
	}

	return 0;
}
