#include <stdio.h>

int main(){
	int n, i;
	
	printf("numero: ");
	scanf("%d", &n);
	
	for(i=1;i<=10;i++){
		printf("%d X %d = %d\n", i, n, (i*n));
	}
	
	return 0;
}
