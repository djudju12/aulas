#include <stdio.h>

int main(){
	int i, n;
	
	printf("digite o numero para saber se eh primo ou nao: ");
	scanf("%d", &n);
	
	for(i=2;i<=(n/2);i++){
		if (n % i == 0){
			printf("%d nao eh primo ", n);
			exit(0);
		}
	}
	printf("%d eh primo", n);
	return 0;
}
