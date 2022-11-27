//Jonathan Willian dos Santos 30/08
#include <stdio.h>

int main() {
	float produtos[] = {23.99, 44.89, 78.10, 12.10, 89.78, 100.00, 250.00, 38.80, 74.87, 11.54, 57.35}, nv_valor, desc;
	int i;

	printf("valor do desconto: ");
	scanf("%f", &desc);

	for(i=0; i<11; i++) {
		nv_valor = (desc/100) * produtos[i];
		printf("Valor do produto %d: %.2f\nValor com %.0f%% de desconto: %.2f\n\n",i+1, produtos[i], desc, (produtos[i]-nv_valor));
	}

	return 0;
}
