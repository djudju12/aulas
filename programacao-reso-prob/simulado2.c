#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#define LTS 118
#define CTS 3
#define LTA 7
#define CTA 18

void printTabela(char simbolos[][CTS], int numAtomicos[][CTA]);
void maximize_window();
int numeroAtomico(char simbolos[][CTS], char simbolo[]);
void acharGrupoPeriodo(int numAtomico, int numAtomicos[][CTA], int *grupo, int *periodo);
void printResultado(char simbolo[], char simbolos[][CTS], int numAtomicos[][CTA]);
void acharFamilia(int grupo, int periodo, int numAtomico, char familia[]);

int main(){
	
	char simbolos[LTS][CTS] = {"H", "He", "Li", "Be", "B", "C", "N",
	"O", "F", "Ne", "Na", "Mg", "Al", "Si", "P", "S", "Cl", "Ar", "K",
	"Ca", "Sc", "Ti", "V", "Cr", "Mn", "Fe", "Co", "Ni", "Cu", "Zn",
	"Ga", "Ge", "As", "Se", "Br", "Kr", "Rb", "Sr", "Y", "Zr", "Nb",
	"Mo", "Tc", "Ru", "Rh", "Pd", "Ag", "Cd", "In", "Sn", "Sb", "Te",
	"I", "Xe", "Cs", "Ba", "La", "Ce", "Pr", "Nd", "Pm", "Sm", "Eu",
	"Gd", "Tb", "Dy", "Ho", "Er", "Tm", "Yb", "Lu", "Hf", "Ta", "W",
	"Re", "Os", "Ir", "Pt", "Au", "Hg", "Tl", "Pb", "Bi", "Po", "At",
	"Rn", "Fr", "Ra", "Ac", "Th", "Pa", "U", "Np", "Pu", "Am", "Cm",
	"Bk", "Cf", "Es", "Fm", "Md", "No", "Lr", "Rf", "Db", "Sg", "Bh",
	"Hs", "Mt", "Ds", "Rg", "Cn", "Nh", "Fl", "Mc", "Lv", "Ts", "Og"};
	
	int numAtomicos[LTA][CTA]={{   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    2},
							   {   3,   4,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   5,   6,   7,   8,   9,   10},
							   {  11,  12,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  13,  14,  15,  16,  17,   18},
							   {  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,   36},
							   {  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  52,  53,   54},
							   {  55,  56,   0,  72,  73,  74,  75,  76,  77,  78,  79,  80,  81,  82,  83,  84,  85,   86},
							   {  87,  88,   0, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,  117, 118} };

	char simbolo[CTS], familia[1000];
	maximize_window();
	
	printTabela(simbolos, numAtomicos);
	while(1){
		printf("Digite o simbolo para consulta (0 para sair): ");
		scanf("%s", simbolo);
		if(simbolo[0] == '0')
			break;
		printResultado(simbolo, simbolos, numAtomicos);
	};
}

void printTabela(char simbolos[][CTS], int numAtomicos[][CTA]){
	int i, j;
	
	printf("\n");
	for (i = 0; i < LTA; i++){
		for (j = 0; j < CTA; j++){
			if (numAtomicos[i][j] != 0)
				printf(" %s\t", simbolos[numAtomicos[i][j] - 1] );
			else printf("\t");
		} printf("\n\n");
	}
}

void printResultado(char simbolo[], char simbolos[][CTS], int numAtomicos[][CTA]){							   
	int numAtomico, periodo, grupo;
	char familia[30];
	
	numAtomico = numeroAtomico(simbolos, simbolo);
	if (!numAtomico){
		printf("Elemento nao encontrado!\n");
		return;
	}
	acharGrupoPeriodo(numAtomico, numAtomicos, &grupo, &periodo);
	acharFamilia(grupo, periodo, numAtomico, familia);
	
	printf("Numero atomico: %d\nPeriodo: %d\nGrupo: %d\nFamilia: %s\n", numAtomico, periodo, grupo, familia);  // TODO: familia
}

int numeroAtomico(char simbolos[][CTS], char simbolo[]){
	int index;
	
	simbolo[0] = toupper(simbolo[0]);
	for (index = 0; index < LTS; index++){
			if (!strcmp(simbolos[index], simbolo))
				return ++index;
		}
	return 0;
}

void acharGrupoPeriodo(int numAtomico, int numAtomicos[][CTA], int *grupo, int *periodo){
	int i, j;
	
	for (i = 0; i < LTA; i++){
		for( j = 0; j < CTA; j++){
			if (numAtomico == numAtomicos[i][j]){
				*periodo = i+1;
				*grupo = j+1;
			}
		}
	}
}

void acharFamilia(int grupo, int periodo, int numAtomico, char familia[]){
	char familias[8][30] = {"Nao metais", "Metais alcalinos", "Semimetais", "Outro metais", "Gases Nobres", "Metais alcalinos-terrosos", "Halogenios", "Metais de transicao"};
	
	if ((periodo <= 4) && ((numAtomico == 1) || (numAtomico == 34) || ((numAtomico >= 6) && (numAtomico <= 8)) || ((numAtomico >= 15) && (numAtomico <= 16))))
		strcpy(familia, familias[0]);
	else if (grupo == 1)
		strcpy(familia, familias[1]);
	else if (((grupo == 13) && (periodo >= 3)) || ((grupo == 14) && (periodo >= 5)) || ((grupo == 15) && (periodo >= 6)) || (numAtomico == 116))
		strcpy(familia, familias[3]);
	else if (grupo == 18)
		strcpy(familia, familias[4]);
	else if (grupo == 2)
		strcpy(familia, familias[5]);
	else if (grupo == 17)
		strcpy(familia, familias[6]);
	else if ((grupo >= 3) && (grupo <= 12))
		strcpy(familia, familias[7]);
	else
		strcpy(familia, familias[2]);
		
	
}

void maximize_window(){
    HWND consoleWindow = GetConsoleWindow();
    ShowWindow(consoleWindow, SW_MAXIMIZE);
}
