#include <stdio.h>
#define TAMANHO 3
int main(){
	int matrix[TAMANHO][TAMANHO] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
	int soma, i, j;
	
	soma = 0;
	for(i=0;i<TAMANHO;i++){
		for(j=0;j<TAMANHO;j++){
			if(j==i)
				soma += matrix[i][j]; 
		}
	}
	
	printf("%d", soma);
	
	return 0;
}
