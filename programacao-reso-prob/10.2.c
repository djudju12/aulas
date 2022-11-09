#include <stdio.h>
#define LINHAS 3
#define COLUNAS 6

void imprimirMatrix(int matrix[][COLUNAS]);

int main(){
	int matrix[LINHAS][COLUNAS], vetor[] = {3, 25, 12, 48, 51, 21, 10, 36, 21, 2, 57, 45, 21, 54, 58, 21, 11, 35};
	int i, j;
	
	for(i=0;i<LINHAS;i++){
		for(j=0;j<COLUNAS;j++){
			matrix[i][j] = vetor[i*COLUNAS+j]; // i=1 j=0 -> vetor[7] -> vetor[14]
		}
	}
	
	imprimirMatrix(matrix);

	
	return 0;
}

void imprimirMatrix(int matrix[][COLUNAS]){
	int i, j;
	
	for(i=0;i<LINHAS;i++){
		for(j=0;j<COLUNAS;j++){
			if(matrix[i][j]<10)
				printf("0%d ", matrix[i][j]);
			else
				printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}

