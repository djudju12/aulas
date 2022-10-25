#include <stdio.h>

int main(){
	int n, i;
	
	printf("n: ");
	scanf("%d", &n);
	
	printf("de 1 ateh %d\n", n);
	for (i=1;i<=n;i++)
		printf("%d ", i);
	printf("\nde %d ateh 0\n", n);
	for(i=n;i>=0;i--)
		printf("%d ", i);
	printf("\nde 0 ateh %d\n", n-1);
	for(i=0;i<n;i++)
		printf("%d ", i);
	

	return 0;
}
