#include <stdio.h>
#include <string.h>
#define N_MAX 1000

typedef struct{
    char str[N_MAX];
    int f;
}NODO;

// converte a string em uma lista
void entrada_dados(char padrao[], NODO *lista){
    int i, lenstr;
    lenstr = strlen(padrao);
    for(i=0;i<lenstr;i++){
        lista->str[i] = padrao[i];
        lista->f++;
    }
}

// exclui nodo na posicao 
void exclui_nodo( int posicao, NODO *lista ){
    int i;
	for( i = posicao; i < lista->f-1; i++)
		lista->str[ i ] = lista->str[ i + 1 ];
	lista->f--;
}

// cria lista
void cria_lista(int *fim){
    *fim=0;
}

// conta diamantes
int diamantes(NODO *lista){
	int contador=0;
	int i=0, j=1;
	// i -> primeiro caractere a ser analisado, j-> último.
	while((lista->f != 0) && (j != lista->f)){  // se i = ultimo elemento ou se a lista estiver com apenas 1 nodo
		// achou um diamante
		if( ( lista->str[i] == '<') && ( lista->str[j] == '>') )
		{
			contador++; 
			// exclui os nodos i e j.
			exclui_nodo(i, lista);
			exclui_nodo(j-1, lista); 
			// volta para o começo da string
			i=0;  
			j=1;
		}
		// se j == ., incrementa a posicao ate encontrar um diamante ou um < 
		else if( ( lista->str[i] == '<') && ( lista->str[j] == '.') )  
			j++;
		// se j for um <, a posicao do i muda para j e o j incrementa
		else 
		{
			i = j;
			j++;
		}
	}
	return contador;
}

int main() {
    NODO lista;
    char padrao[N_MAX];
    int resultado, inputs;
    int i;
    
    
    fflush(stdin);
    scanf("%d", &inputs); // quantidade de casos testes
    for(i=0;i<inputs;i++){
        fflush(stdin);
        scanf("%s", padrao); // string
        cria_lista( &lista.f );
        entrada_dados(padrao, &lista);
        resultado = diamantes(&lista);
        printf("%d\n", resultado);
    }
    
    return 0;
}
