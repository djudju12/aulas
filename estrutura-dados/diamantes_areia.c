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
	int i=0, j=1, y;
	// i -> primeiro caractere a ser analisado, j-> último.
	while((lista->f != 0)){  // se i = ultimo elemento ou se a lista estiver com apenas 1 nodo
		if(j == lista->f)
			break;
		if( ( lista->str[i] == '<') && ( lista->str[j] == '>') )
		{
			contador++; // achou um diamante <.<..>
			for(y=0;y<=j-i;y++)  // j-i -> distancia do nodo i ao j
				exclui_nodo(i, lista); // exclui os nodos entre i e j. Ao excluir o nodo = i, todos os nodos = -1, por isso sempre é excluido o nodo i
			// volta para o começo da string
			i=0;  
			j=1;
			
		}
		else if( ( lista->str[i] == '<') && ( lista->str[j] == '.') )  // verifica se o ultimo caractere da substring é ., se sim entao compara com o proximo
			j++;
		else if( ( lista->str[i] == '<') && ( lista->str[j] == '<') )  // verifica se o ultimo caractere da substring é <, se sim começa a analisar a partir do ultimo elemento da substring
		{
			i = j;
			j++;
		}
		else if( ( lista->str[i] == '>') || ( lista->str[i] == '.') ) // verifica se o primeiro caractere da substring é ou . ou >, se sim começa a analisar a partir do ultimo elemento da substring
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
