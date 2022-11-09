#include <stdio.h>
#define LINHAS 2
#define COLUNAS 3

void imprimirMatrix(int matrix[][COLUNAS]);

int main(){
	int matrix[][2] = {{1, 2}, {3, 4}, {5, 6}}, matrixT[LINHAS][COLUNAS];
	int i, j;
	
	for(i=0;i<2;i++){
		for(j=0;j<3;j++){
			matrixT[i][j] = matrix[j][i];
		}
	}
	
	imprimirMatrix(matrixT);
	
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

