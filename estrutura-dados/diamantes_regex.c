#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <conio.h>
#define N_MAX 1000

typedef struct{             
       char caracter;
}INFORMACAO;

typedef struct{
    INFORMACAO info[N_MAX];
    int f;
}NODO;

void entrada_dados(char str[], NODO *lista){
    int i, lenstr;
    lenstr = strlen(str);
    for(i=0;i<lenstr;i++){
        lista->info[i].caracter = str[i];
        lista->f++;
    }
}

void exclui_nodo( int posicao, NODO *lista ){
    int i;
    
	for( i = posicao; i < lista->f-1; i++)
		lista->info[ i ] = lista->info[ i + 1 ];
	lista->f--;
}

void cria_lista(int *fim){
    *fim=0;
}

void lista_to_strig(char str[], NODO *lista){
    char aux[N_MAX];
    char extension; 
    int i;
    
    for(i=0;i<lista->f;i++){
        aux[i] = lista->info[i].caracter;
    }
    strcpy(str, aux);
}

int offsets_reg(NODO *lista){
    regex_t preg;
    char regex[] = "<[\\.]*>";
    int ret, cflags = REG_ICASE;
    char str[N_MAX];

    lista_to_strig( str, lista );

    regmatch_t pmatch[2] = {{-1,-1},{-1,-1}};
    ret = regcomp(&preg, regex, cflags);
    ret = regexec(&preg, str, 2, pmatch, 0);

    int count=0;
    while(!ret){
        int inicio, fim, i;
        inicio = pmatch[0].rm_so; // primeiro
        fim = pmatch[0].rm_eo - 1; // segundo
        for(i=0;i<=fim-inicio;i++)
            exclui_nodo(inicio, lista);
        count++;
        lista_to_strig( str, lista );
        ret = regcomp(&preg, regex, cflags);
        ret = regexec(&preg, str, 2, pmatch, 0);
    }
    return count;
}

int main() {
    NODO lista;
    char teste[N_MAX];
    int resultado, inputs;
    int i;
    
    fflush(stdin);
    scanf("%d", &inputs);
    for(i=0;i<inputs;i++){
        fflush(stdin);
        scanf("%s", teste);
        cria_lista( &lista.f );
        entrada_dados(teste, &lista);
        resultado = offsets_reg(&lista);
        printf("%d\n", resultado);
    }

    return 0;
}