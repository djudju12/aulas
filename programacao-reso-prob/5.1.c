//Jonathan Willian dos Santos 30/08
#include <stdio.h>

int main() {
	float notas[30] =  {10.0,
	                    9.9, 9.8, 9.5, 8.5, 7.0, 7.2, 6.6, 4.8, 7.8, 8.8,
	                    9.9, 10.0, 9.7, 8.6, 8.8, 10.0, 7.9, 6.9, 8.9,
	                    5.9, 7.8, 9.7, 8.6, 6.9, 10.0, 9.1, 9.3, 8.2,
	                    7.4
	                   }, media, som=0;
	int i, cont=0;
	
	for (i=0;i<30;i++){
		if (notas[i]>=7){
		som += notas[i];
		cont++;
		}
	}
	media = som / cont;
	printf("soma = %f\ncontador = %d\nmedia = %f", som, cont, media);
	
	return 0;
}
