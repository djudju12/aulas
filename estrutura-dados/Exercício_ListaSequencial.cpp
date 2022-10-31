/***********************************************/ 
/* Lista Sequencial                            */
/* objetivo: controle de registros             */
/* programador: Daniela Bagatini               */
/* criado em: 09/11/2020                       */
/* data da última alteração: 31/10/2022        */
/***********************************************/

/***********************************************/
/* Definição das Bibliotecas                   */
/***********************************************/
#include <stdio.h>         // entrada e saída padrão: printf, scanf
#include <stdlib.h>		   // exit, system
#include <string.h>	  	   // strcmp - comparar strings
#include <locale.h>        // setlocale - alterar idioma para português
//#include <ctype.h>       // toupper - converter caracter para maiúsculo
//#include <conio.h>       // getch - ler do tecla

// bibliotecas incluídas, manter bibliotecas na mesma pasta do arquivo fonte
#include "MODELOSEQ.h"     // modelo de dados
#include "GERA_DADOSSEQ.h" // gera dados para povoar lista de forma automática 


/***********************************************/
/* Definição das Funções                       */
/***********************************************/
void entrada_dados   ( INFORMACAO *aux );     // lê dos dados de entrada
void imprime_lista   ( NODO lista );          // visualiza lista em tela
void cria_lista      ( int *fim );            // inicializa lista com tamanho 0
void inclui_fim      ( NODO *lista );         // inclui novo registro no final da lista
void inclui_inicio   ( NODO *lista );         // inclui novo registro no início da lista
void exclui_nodo     ( NODO *lista );         // exclui regitro por código
void consulta_nome   ( NODO lista );          // consulta registro por nome e apresenta demais dados do registro
void ordena_lista    ( NODO *lista );         // ordena por código - ordem crescente 
void altera_nodo     ( NODO *lista );         // altera regitro a partir de um código de referência

// outras funções complementares
int  procura_nodo    ( int cod, NODO lista ); // procura por código na lista
void inclui_antes    ( NODO *lista );         // inclui novo registro antes de um código de referência
void inclui_depois   ( NODO *lista );         // inclui novo registro depois de um código de referência
// crie sua própria função aqui!


/***********************************************/
/* Programa Principal                          */
/***********************************************/
int main( void ){
    int op;                                   // opção do menu
    NODO lista;                               // variável do tipo lista sequencial = vetor de registros
    setlocale( LC_ALL, "Portuguese" );        // alterar idioma para português

    while( 1 ){
         printf( "\n /--------------------------------------------------------/" );
         printf( "\n Programa registro - Menu                                  " );
         printf( "\n [1 ] Cria lista                                           " );
         printf( "\n [2 ] Inclui registro no final da lista                    " );
         printf( "\n [3 ] Inclui registro no início da lista                   " );
         printf( "\n [4 ] Inclui registro antes de um código de referência     " );
         printf( "\n [5 ] Inclui registro depois de um código de referência    " );
         printf( "\n [6 ] Exclui registro                                      " );
         printf( "\n [7 ] Ordena lista                                         " );
         printf( "\n [8 ] Altera registro                                      " );  
		 printf( "\n [9 ] Consulta por nome                                    " );                                         
         printf( "\n [10] Gera dados                                           " ); 
		 printf( "\n [11] Imprime lista                                        " );
         printf( "\n [0 ] Para sair do programa                                " );
         printf( "\n /--------------------------------------------------------/" );
         printf( "\n Opção: " );
         fflush( stdin );    // limpa buffer do teclado, funciona antes da entrada de dados
         scanf( "%i", &op ); // tecla de opção do menu
         
         switch( op ) {
            case 1:  // rotina cria lista, inicializa a lista
                    cria_lista( &lista.f );
                    break;

            case 2:  // rotina inclui registro no final da lista, conforme indicado pelo gerenciados da lista (posição lista.f)
                    inclui_fim( &lista );
                    break;

            case 3:  // rotina inclui registro no início da lista, posição 0
                    inclui_inicio( &lista );
                    break;

            case 4:  // rotina inclui registro antes de um código de referência informado
                     inclui_antes( &lista );
                     break;

            case 5:  // rotina inclui registro depois de um código de referência informado
                    inclui_depois( &lista );
                    break;

            case 6:  // rotina exclui registro conforme código de referência
                    exclui_nodo( &lista );
                    break;

            case 7: // rotina ordena lista por código, ordem crescente
                    ordena_lista( &lista );
                    break;
                    
            case 8: // rotina altera registro com base no código de referência informado
                    altera_nodo( &lista );
                    break;
                    
            case 9: // rotina consulta por nome e apresentada demais dados do registro
                    consulta_nome( lista ); 
                    break;  

            case 10: // rotina gera dados de forma automática para povoar a lista
                    gera_dados( &lista );
                    break;      
                                                               
            case 11: // rotina imprime todos os registros da lista
                    imprime_lista( lista );
                    break;
                    
            case 0: // término do programa
                    exit( 1 );
                    break;

            default :
                    printf( "\n Digite uma opção!" );
                    break;
        } // fim switch( op )
        
        printf("\n");
        getchar();       // parada da tela
        system( "cls" ); // limpar tela
     } // fim do while( 1 )
 return 0;
} // fim do programa principal



/************************************************
 * entrada_dados                                *
 * objetivo: ler dados para novo registro       *
 * entrada : registro aux (auxiliar)            *
 * saída   : aux atualizado com dados           *
 ************************************************/
void entrada_dados( INFORMACAO *aux ){
	 
    printf( "\n\n Digite o código: " );
    fflush( stdin );                        // limpa buffer do teclado, funciona junto com entrada de dados
    scanf( "%d", &aux->codigo );

    printf( "\n Digite o nome: " );
    fflush( stdin );     
    gets( aux->nome );
}



/*************************************************
 * imprime_lista                                 *
 * objetivo: imprimir dados em tela              *
 * entrada : lista                               *
 * saída   : nenhuma, apenas em tela             *
 *************************************************/
void imprime_lista( NODO lista ){
     
    int i;                                // índice do laço

    if( lista.f == 0 )                    // verifica se lista vazia
        printf( "\n Lista vazia! " );
    else{
        printf("\n /Relatório Geral ----------------------------------------/ ");
	    for( i = 0 ; i < lista.f ; i++ ) { // percorre a lista e imprime dados
	         printf( "\n Registro[%d]", i );
	         printf( "\t Código.: %d", lista.info[ i ].codigo );
	         printf( "\t Nome.: %s", lista.info[ i ].nome );
	    }
    }    
    getchar();                             // parada da tela
}



/************************************************
 * cria_lista                                   *
 * objetivo: inicializar a lista                *
 * entrada : fim da lista                       *
 * saída   : fim da lista atualizado, com 0     *
 ************************************************/
void cria_lista( int *fim ){
     
    *fim = 0;                                   // iniciliza lista, tamanho da lista = 0
    printf( "\n Lista criada! " );
}



/************************************************
 * inclui_fim                                   *
 * objetivo: inserir registro no fim da lista   *
 * entrada : lista                              *
 * saída   : lista com novo elemento            *
 ***********************************************/
void inclui_fim( NODO *lista ){
     

}



/************************************************
 * inclui_início                                *
 * objetivo: inserir registro no início da lista*
 * entrada : lista                              *
 * saída   : lista com novo elemento            *
 ************************************************/
void inclui_inicio( NODO *lista ){
     

}



/************************************************
 * procura_nodo                                 *
 * objetivo: achar posição de referência        *
 * entrada : código de referência e lista       *
 * saída   : posição física da referência ou -1 *
 ************************************************/
int procura_nodo( int cod, NODO lista ){
        
    int i= 0;                                   // i = índice

    while(( i < lista.f ) && ( cod != lista.info[ i ].codigo )) // anda pela lista até o final ou ate encontrar código desejado
            i++;
    if( cod == lista.info[ i ].codigo )         // se encontou código igual    
        return( i );                            // retorna posição física do nodo de referência
    else       
        return( -1 );                           // retorna código não encontrado
}



/************************************************
 * exclui_nodo                                  *
 * objetivo: excluir por código de referência   *
 * entrada : lista                              *
 * saída   : lista com um elemento removido     *
 ************************************************/
void exclui_nodo( NODO *lista ){
     

}



/************************************************
* ordena_lista                                  *
* objetivo: ordenar lista por código crescente  *
* entrada : lista                               *
* saída   : lista ordenada                      *
*************************************************/
void ordena_lista( NODO *lista ){              // Algoritmo Método Bolha - Bubble Sort
     
 
}


/************************************************
 * altera_nodo                                  *
 * objetivo: alterar registro de referência     *
 * entrada : lista                              *
 * saída   : lista com um elemento alterado     *
 ************************************************/
void altera_nodo( NODO *lista ){
        

}             


/************************************************
 * consulta_nome                                *
 * objetivo: consultar registro por nome        *
 * entrada : lista                              *
 * saída   : nenhuma, dados em tela             *
 ************************************************/
void consulta_nome( NODO lista ){

}

/************************************************
 * inclui_antes                                 *
 * objetivo: inserir antes de código referência *
 * entrada : lista                              *
 * saída   : lista com novo elemento            *
 ************************************************/
void inclui_antes( NODO *lista ){
     
    if( lista->f == N_MAX )                     // verifica se a lista esta cheia
        printf( "\n Lista cheia! " );
    else{
        int i, cod, pf = 0;                     // i= índice; cod= código de referência; pf= posicao fisica do codigo de referencia         
        printf( "\n Código de referência: " );
        fflush( stdin );
        scanf( "%d", &cod );                   // limpa buffer do teclado, funciona junto com entrada de dados
        pf= procura_nodo( cod, *lista );       // procura código de referência

        if( ( pf >= 0 ) && ( pf < lista->f ) && ( lista->info[ pf ].codigo == cod ) ){ // verifica se a posição e o codigo são válidos
              INFORMACAO aux;                         // auxiliar para a entrada de dados
              entrada_dados( &aux );                  // lê dados
              for( i = lista->f - 1 ; i >= pf ; i-- ) // desloca a lista até abrir um espaço antes do nodo de referência
                   lista->info[ i + 1 ]= lista->info[ i ];
              lista->info[ pf ] = aux;                // insere na lista
              lista->f++;                             // incrementa o tamanho da lista//mencpy(&lista.info[lista.f], &aux, sizeof(NODO));
              printf( "\n Registro incluido antes do nodo de referência!" );
         }else 
              printf( "\n Nodo de referência não existe!" );
    } 
}



/************************************************
 * inclui_depois                                *
 * objetivo: inserir após de código referência  *
 * entrada : lista                              *
 * saída   : lista com novo elemento            *
 ************************************************/
void inclui_depois( NODO *lista ){
 
    if( lista->f == N_MAX )                     // verifica se a lista está cheia
        printf( "\n Lista cheia! " );
    else{
        int i, cod, pf = 0;                     // i= índice; cod= código de referência; pf= posição física do código de referência         
        printf( "\n Código de referência: " );
        fflush( stdin );
        scanf( "%d", &cod );                    // limpa buffer do teclado, funciona junto com entrada de dados
        pf = procura_nodo( cod, *lista );       // procura código de referência

        if( ( pf >= 0 ) && ( pf < lista->f ) && ( lista->info[ pf ].codigo == cod ) ){ // verifica se a posição e o código são válidos
              INFORMACAO aux;                        // auxiliar para a entrada de dados
              entrada_dados( &aux );                 // lê dados
              for ( i = lista->f - 1 ; i > pf ; i-- )// desloca da lista até abrir espaço depois do nodo de referência
                    lista->info[ i + 1 ] = lista->info[ i ];
              lista->info[ pf + 1 ] = aux;           // insere na lista
              lista->f++;                            // incrementa o tamanho da lista //mencpy(&lista.info[lista.f], &aux, sizeof(NODO));
              printf( "\n Registro incluido depois do nodo de referência! " );
         }else 
              printf( "\n Nodo de referência nao existe! " );
    } 
}
