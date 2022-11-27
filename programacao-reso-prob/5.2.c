//Jonathan Willian dos Santos 30/08
#include <stdio.h>
#define N 10

int main(){
	char palavra[N];
	int i;
	
	printf("Digite uma palavra de %d letras ", N);
	scanf("%s", palavra);
	
	for(i=0;i<N;i++)
		printf("%c\n", palavra[i]);
	
	return 0;
}
