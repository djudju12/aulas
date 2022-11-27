#include <stdio.h>

int main(){
	float area, d_maior, d_menor;
	
	printf("Diagonal maior: ");
	scanf("%f", &d_maior);
	printf("Diagonal menor: ");
	scanf("%f", &d_menor);
	
	area = d_maior * d_menor / 2;
	printf("Area do losango = %.2f", area);
	
	return 0;
}
