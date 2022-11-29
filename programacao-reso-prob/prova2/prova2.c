/*
	Aluno: Jonathan Willian dos Santos
	Matricula: 102134
	Data: 29/11/2022
	Disciplina: Programação para Resolução de Problemas - UNISC
*/

#include <stdio.h>
#include "funcoes_prova2.h"

#define MESES 12 // Quantidade de meses em um ano
#define DIAS_SEMANA 7 // Quantidade de dias em uma semana
#define MAX_STR 100 // Tamanho maximo de uma string
#define LINHAS_CALENDARIO 6  // Quantidade de linhas por calendario

//-----Funções para imprimir o calendario-----//
// Printa o calendario do mês m. Função auxiliar 
void printCalendario(int m, int ano, int matrix[LINHAS_CALENDARIO][DIAS_SEMANA]);
// Printa os 12 calendarios respectivos de cada mês
void printCalendarioCompleto(int ano, int matrix[LINHAS_CALENDARIO][DIAS_SEMANA]);
//--------------------------------------------//

// Função para manipular a contagem de n dias a partir da data fornecida
void contarDias(int *dia, int *mes, int *ano, int n);

// Função para imprimir o dia da semana da data fornecida
void imprimirWeekday(int dia, int mes, int ano);




int main(){
	int c[LINHAS_CALENDARIO][DIAS_SEMANA]; // Matriz que armazena o calendario
	int nDias; // variavel que armazena quantos dias serão contados
	int dia, mes, ano; // Variaveis das datas
	
//	printf("Informe dia, mes e ano: ");
//	scanf("%d %d %d", &dia, &mes, &ano);
//	imprimirWeekday(dia, mes, ano);
//	
//	printf("Quantos dias deseja adicionar nessa data? ");
//	scanf("%d", &nDias);
//	
//	contarDias(&dia, &mes, &ano, nDias);
//	printf("A nova data eh: %d/%d/%d\n", dia, mes, ano);
//	
	printf("Deseja imprimir o calendario de qual ano? ");
	scanf("%d", &ano);
	printCalendarioCompleto(ano, c);
}

void printCalendario(int m, int ano, int matrix[LINHAS_CALENDARIO][DIAS_SEMANA])
{
	// Dias do ano
	char meses_str[MESES][MAX_STR] = {"Janeiro", "Fevereiro", "Marco", "Abril", "Maio", "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};
	int espacoCalendario = DIAS_SEMANA * 3; // cada calendarios ocupa 7 (dia da semana) x 3 (espaços em branco por dia) espaços nas linhas
	
	calendario(m, ano, matrix);  //Monta a matriz da data
	int b;
	for (b = 0; b < espacoCalendario; b++) printf("-"); 
	printf("\nMes de %s\n", meses_str[m-1]);  // Imprime o mês correspondente
	printf("D  S  T  Q  Q  S  S\n");  // cabeçalho
	int i, j;
	for(i=0; i<6; i++){		// linhas são as semanas
		for(j=0; j<7; j++){		// colunas são os dias da semana
			if (matrix[i][j] == 0) printf("   "); //Printa 3 espaços, 2 pois os numeros estao formatos com 2 digitos e 1 para o esapaço entre eles
			else printf("%02d ", matrix[i][j]);  //%02d -> 2 casas iniciando com 0
		}
		printf("\n");
	}
	for (b = 0; b < espacoCalendario; b++) printf("-");  // Imprime as barras dos calendarios
	printf("\n");
}

void contarDias(int *dia, int *mes, int *ano, int n)
{
	while (n > 0){
		if (*dia == ultimo_dia_mes(*mes, *ano)){ // Se dia == ultimo dia do mes, troca o mes e volta para o primeiro dia
			*dia = 1;
			*mes += 1;
			if (*mes > MESES){ // se o mês == 13, ou seja, acabou o mês 12 -> mes = 1 e avança o ano
				*mes = 1;
				*ano += 1;
			}
		}
		else *dia += 1; // Se não for o ultimo dia do mes ou do ano, apenas incrimenta o dia
		n--; 
	}
}

void imprimirWeekday(int dia, int mes, int ano)
{
	// Dias da semana
	char weekdays[][MAX_STR] = {"Domingo", "Segunda", "Terca", "Quarta", "Quinta", "Sexta", "Sabado"};
	int weekday = dia_semana(dia, mes, ano); // Retorna o dia da semana em inteiro
	printf("Foi(eh) um(a) %s\n", weekdays[weekday-1]); // Imprime o respectivo dia da semana em string
}

void printCalendarioCompleto(int ano, int matrix[LINHAS_CALENDARIO][DIAS_SEMANA])
{
	// Imprime cada um dos 12 meses do calendario
	int i;
	for (i = 1; i <= MESES; i++)
		printCalendario(i, ano, matrix);

}

