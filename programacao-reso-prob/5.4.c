//Jonathan Willian dos Santos 30/08
#include <stdio.h>
#include <locale.h>

int main() {
	int i;
	float notas[5];

	setlocale(LC_ALL, "Portuguese");

	for(i=0; i<5; i++) {
		printf("Nota do aluno %d: \n", i+1);
		scanf("%f", &notas[i]);
	}
	for(i=0; i<5; i++) {
		if(notas[i] == 10.0)
			printf("PARABÉNS Aluno %d, tirou nota %.2f\n", i+1, notas[i]);
		else
			printf("Aluno %d tirou nota %.2f\n", i+1, notas[i]);
	}

	return 0;
}
