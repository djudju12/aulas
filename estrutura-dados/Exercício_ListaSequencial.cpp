/***********************************************/ 
/* Lista Sequencial                            */
/* objetivo: controle de registros             */
/* programador: Daniela Bagatini               */
/* criado em: 09/11/2020                       */
/* data da �ltima altera��o: 31/10/2022        */
/***********************************************/

/***********************************************/
/* Defini��o das Bibliotecas                   */
/***********************************************/
#include <stdio.h>         // entrada e sa�da padr�o: printf, scanf
#include <stdlib.h>		   // exit, system
#include <string.h>	  	   // strcmp - comparar strings
#include <locale.h>        // setlocale - alterar idioma para portugu�s
//#include <ctype.h>       // toupper - converter caracter para mai�sculo
//#include <conio.h>       // getch - ler do tecla

// bibliotecas inclu�das, manter bibliotecas na mesma pasta do arquivo fonte
#include "MODELOSEQ.h"     // modelo de dados
#include "GERA_DADOSSEQ.h" // gera dados para povoar lista de forma autom�tica 


/***********************************************/
/* Defini��o das Fun��es                       */
/***********************************************/
void entrada_dados   ( INFORMACAO *aux );     // l� dos dados de entrada
void imprime_lista   ( NODO lista );          // visualiza lista em tela
void cria_lista      ( int *fim );            // inicializa lista com tamanho 0
void inclui_fim      ( NODO *lista );         // inclui novo registro no final da lista
void inclui_inicio   ( NODO *lista );         // inclui novo registro no in�cio da lista
void exclui_nodo     ( NODO *lista );         // exclui regitro por c�digo
void consulta_nome   ( NODO lista );          // consulta registro por nome e apresenta demais dados do registro
void ordena_lista    ( NODO *lista );         // ordena por c�digo - ordem crescente 
void altera_nodo     ( NODO *lista );         // altera regitro a partir de um c�digo de refer�ncia

// outras fun��es complementares
int  procura_nodo    ( int cod, NODO lista ); // procura por c�digo na lista
void inclui_antes    ( NODO *lista );         // inclui novo registro antes de um c�digo de refer�ncia
void inclui_depois   ( NODO *lista );         // inclui novo registro depois de um c�digo de refer�ncia
// crie sua pr�pria fun��o aqui!


/***********************************************/
/* Programa Principal                          */
/***********************************************/
int main( void ){
    int op;                                   // op��o do menu
    NODO lista;                               // vari�vel do tipo lista sequencial = vetor de registros
    setlocale( LC_ALL, "Portuguese" );        // alterar idioma para portugu�s

    while( 1 ){
         printf( "\n /--------------------------------------------------------/" );
         printf( "\n Programa registro - Menu                                  " );
         printf( "\n [1 ] Cria lista                                           " );
         printf( "\n [2 ] Inclui registro no final da lista                    " );
         printf( "\n [3 ] Inclui registro no in�cio da lista                   " );
         printf( "\n [4 ] Inclui registro antes de um c�digo de refer�ncia     " );
         printf( "\n [5 ] Inclui registro depois de um c�digo de refer�ncia    " );
         printf( "\n [6 ] Exclui registro                                      " );
         printf( "\n [7 ] Ordena lista                                         " );
         printf( "\n [8 ] Altera registro                                      " );  
		 printf( "\n [9 ] Consulta por nome                                    " );                                         
         printf( "\n [10] Gera dados                                           " ); 
		 printf( "\n [11] Imprime lista                                        " );
         printf( "\n [0 ] Para sair do programa                                " );
         printf( "\n /--------------------------------------------------------/" );
         printf( "\n Op��o: " );
         fflush( stdin );    // limpa buffer do teclado, funciona antes da entrada de dados
         scanf( "%i", &op ); // tecla de op��o do menu
         
         switch( op ) {
            case 1:  // rotina cria lista, inicializa a lista
                    cria_lista( &lista.f );
                    break;

            case 2:  // rotina inclui registro no final da lista, conforme indicado pelo gerenciados da lista (posi��o lista.f)
                    inclui_fim( &lista );
                    break;

            case 3:  // rotina inclui registro no in�cio da lista, posi��o 0
                    inclui_inicio( &lista );
                    break;

            case 4:  // rotina inclui registro antes de um c�digo de refer�ncia informado
                     inclui_antes( &lista );
                     break;

            case 5:  // rotina inclui registro depois de um c�digo de refer�ncia informado
                    inclui_depois( &lista );
                    break;

            case 6:  // rotina exclui registro conforme c�digo de refer�ncia
                    exclui_nodo( &lista );
                    break;

            case 7: // rotina ordena lista por c�digo, ordem crescente
                    ordena_lista( &lista );
                    break;
                    
            case 8: // rotina altera registro com base no c�digo de refer�ncia informado
                    altera_nodo( &lista );
                    break;
                    
            case 9: // rotina consulta por nome e apresentada demais dados do registro
                    consulta_nome( lista ); 
                    break;  

            case 10: // rotina gera dados de forma autom�tica para povoar a lista
                    gera_dados( &lista );
                    break;      
                                                               
            case 11: // rotina imprime todos os registros da lista
                    imprime_lista( lista );
                    break;
                    
            case 0: // t�rmino do programa
                    exit( 1 );
                    break;

            default :
                    printf( "\n Digite uma op��o!" );
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
 * sa�da   : aux atualizado com dados           *
 ************************************************/
void entrada_dados( INFORMACAO *aux ){
	 
    printf( "\n\n Digite o c�digo: " );
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
 * sa�da   : nenhuma, apenas em tela             *
 *************************************************/
void imprime_lista( NODO lista ){
     
    int i;                                // �ndice do la�o

    if( lista.f == 0 )                    // verifica se lista vazia
        printf( "\n Lista vazia! " );
    else{
        printf("\n /Relat�rio Geral ----------------------------------------/ ");
	    for( i = 0 ; i < lista.f ; i++ ) { // percorre a lista e imprime dados
	         printf( "\n Registro[%d]", i );
	         printf( "\t C�digo.: %d", lista.info[ i ].codigo );
	         printf( "\t Nome.: %s", lista.info[ i ].nome );
	    }
    }    
    getchar();                             // parada da tela
}



/************************************************
 * cria_lista                                   *
 * objetivo: inicializar a lista                *
 * entrada : fim da lista                       *
 * sa�da   : fim da lista atualizado, com 0     *
 ************************************************/
void cria_lista( int *fim ){
     
    *fim = 0;                                   // iniciliza lista, tamanho da lista = 0
    printf( "\n Lista criada! " );
}



/************************************************
 * inclui_fim                                   *
 * objetivo: inserir registro no fim da lista   *
 * entrada : lista                              *
 * sa�da   : lista com novo elemento            *
 ***********************************************/
void inclui_fim( NODO *lista ){
     

}



/************************************************
 * inclui_in�cio                                *
 * objetivo: inserir registro no in�cio da lista*
 * entrada : lista                              *
 * sa�da   : lista com novo elemento            *
 ************************************************/
void inclui_inicio( NODO *lista ){
     

}



/************************************************
 * procura_nodo                                 *
 * objetivo: achar posi��o de refer�ncia        *
 * entrada : c�digo de refer�ncia e lista       *
 * sa�da   : posi��o f�sica da refer�ncia ou -1 *
 ************************************************/
int procura_nodo( int cod, NODO lista ){
        
    int i= 0;                                   // i = �ndice

    while(( i < lista.f ) && ( cod != lista.info[ i ].codigo )) // anda pela lista at� o final ou ate encontrar c�digo desejado
            i++;
    if( cod == lista.info[ i ].codigo )         // se encontou c�digo igual    
        return( i );                            // retorna posi��o f�sica do nodo de refer�ncia
    else       
        return( -1 );                           // retorna c�digo n�o encontrado
}



/************************************************
 * exclui_nodo                                  *
 * objetivo: excluir por c�digo de refer�ncia   *
 * entrada : lista                              *
 * sa�da   : lista com um elemento removido     *
 ************************************************/
void exclui_nodo( NODO *lista ){
     

}



/************************************************
* ordena_lista                                  *
* objetivo: ordenar lista por c�digo crescente  *
* entrada : lista                               *
* sa�da   : lista ordenada                      *
*************************************************/
void ordena_lista( NODO *lista ){              // Algoritmo M�todo Bolha - Bubble Sort
     
 
}


/************************************************
 * altera_nodo                                  *
 * objetivo: alterar registro de refer�ncia     *
 * entrada : lista                              *
 * sa�da   : lista com um elemento alterado     *
 ************************************************/
void altera_nodo( NODO *lista ){
        

}             


/************************************************
 * consulta_nome                                *
 * objetivo: consultar registro por nome        *
 * entrada : lista                              *
 * sa�da   : nenhuma, dados em tela             *
 ************************************************/
void consulta_nome( NODO lista ){

}

/************************************************
 * inclui_antes                                 *
 * objetivo: inserir antes de c�digo refer�ncia *
 * entrada : lista                              *
 * sa�da   : lista com novo elemento            *
 ************************************************/
void inclui_antes( NODO *lista ){
     
    if( lista->f == N_MAX )                     // verifica se a lista esta cheia
        printf( "\n Lista cheia! " );
    else{
        int i, cod, pf = 0;                     // i= �ndice; cod= c�digo de refer�ncia; pf= posicao fisica do codigo de referencia         
        printf( "\n C�digo de refer�ncia: " );
        fflush( stdin );
        scanf( "%d", &cod );                   // limpa buffer do teclado, funciona junto com entrada de dados
        pf= procura_nodo( cod, *lista );       // procura c�digo de refer�ncia

        if( ( pf >= 0 ) && ( pf < lista->f ) && ( lista->info[ pf ].codigo == cod ) ){ // verifica se a posi��o e o codigo s�o v�lidos
              INFORMACAO aux;                         // auxiliar para a entrada de dados
              entrada_dados( &aux );                  // l� dados
              for( i = lista->f - 1 ; i >= pf ; i-- ) // desloca a lista at� abrir um espa�o antes do nodo de refer�ncia
                   lista->info[ i + 1 ]= lista->info[ i ];
              lista->info[ pf ] = aux;                // insere na lista
              lista->f++;                             // incrementa o tamanho da lista//mencpy(&lista.info[lista.f], &aux, sizeof(NODO));
              printf( "\n Registro incluido antes do nodo de refer�ncia!" );
         }else 
              printf( "\n Nodo de refer�ncia n�o existe!" );
    } 
}



/************************************************
 * inclui_depois                                *
 * objetivo: inserir ap�s de c�digo refer�ncia  *
 * entrada : lista                              *
 * sa�da   : lista com novo elemento            *
 ************************************************/
void inclui_depois( NODO *lista ){
 
    if( lista->f == N_MAX )                     // verifica se a lista est� cheia
        printf( "\n Lista cheia! " );
    else{
        int i, cod, pf = 0;                     // i= �ndice; cod= c�digo de refer�ncia; pf= posi��o f�sica do c�digo de refer�ncia         
        printf( "\n C�digo de refer�ncia: " );
        fflush( stdin );
        scanf( "%d", &cod );                    // limpa buffer do teclado, funciona junto com entrada de dados
        pf = procura_nodo( cod, *lista );       // procura c�digo de refer�ncia

        if( ( pf >= 0 ) && ( pf < lista->f ) && ( lista->info[ pf ].codigo == cod ) ){ // verifica se a posi��o e o c�digo s�o v�lidos
              INFORMACAO aux;                        // auxiliar para a entrada de dados
              entrada_dados( &aux );                 // l� dados
              for ( i = lista->f - 1 ; i > pf ; i-- )// desloca da lista at� abrir espa�o depois do nodo de refer�ncia
                    lista->info[ i + 1 ] = lista->info[ i ];
              lista->info[ pf + 1 ] = aux;           // insere na lista
              lista->f++;                            // incrementa o tamanho da lista //mencpy(&lista.info[lista.f], &aux, sizeof(NODO));
              printf( "\n Registro incluido depois do nodo de refer�ncia! " );
         }else 
              printf( "\n Nodo de refer�ncia nao existe! " );
    } 
}
