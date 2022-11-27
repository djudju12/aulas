#include <stdio.h>
#define P1 0.2
#define P2 0.3
#define P3 0.5

int main(){
	float n1, n2, n3, media;
	
	printf("Digite a nota 1: ");
	scanf("%f", &n1);
	printf("Digite a nota 2: ");
	scanf("%f", &n2);
	printf("Digite a nota 3: ");
	scanf("%f", &n3);
	
	media = n1*P1 + n2*P2 + n3*P3;
	printf("%.2f", media);  
	
	return 0;
}
