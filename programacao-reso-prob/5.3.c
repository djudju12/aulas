//Jonathan Willian dos Santos 30/08
#include <stdio.h>

int main(){
	int meu_vetor[10] = {-1, 8, 9, -8, -777, 6, 4, 0, 3, 777}, i;
	
	for(i=0;i<10;i++){
		if(meu_vetor[i] < 0)
			printf("indice = %d, valor %d\n", i, meu_vetor[i]);
	}
	
	return 0;
}
