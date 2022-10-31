/***********************************************/ 
/* Defini��o do Registro e da Estrutura        */
/* Profa Daniela Bagatini                      */
/***********************************************/ 
#define N_MAX   6

typedef struct{                 // registro pessoa, utilize os dados necess�rios
       int  codigo;
       char nome[30];
}INFORMACAO;
       
typedef struct{
       INFORMACAO info[N_MAX];  // dados do registro
       int f;                   // n�mero de registro(s) ocupado(s) na estrutura
}NODO;                          // estrutura do tipo NODO
