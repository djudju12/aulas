/***********************************************/ 
/* Biblioteca para Lista Sequencial            */
/* Profa Daniela Bagatini                      */
/***********************************************/ 
#include <string.h>
#include <time.h>

/************************************************
 * aleatorio                                    *
 * objetivo: rotina para gerar um número        *
 * aleatório de um valor máximo estipulado      *
 * entrada : max                                *
 * saída   : número aleatório                   *
 ************************************************/
int aleatorio( int max ){
	
	int ret = rand() % max; // gera número com base em max = número máximo
	return ret;
}


/************************************************
 * gera_dados                                   *
 * objetivo: rotina para ler dados dos registros*
 * entrada : lista                              *
 * saída   : lista atualizada com dados         *
 ***********************************************/
void gera_dados( NODO *lista ){
	 
	char  nomeTemp[50];                        // armazena nome e sobrenome temporariamente
	int   i, x;                                // i= índice da lista; x= armazena número sorteado 
	
	//Fonte dos nomes: https://petitebox.com.br/blog/100-nomes-mais-comuns-no-brasil-em-2016/
	char *nomes[] = {"Miguel",
"Arthur",
"Davi",
"Bernardo",
"Heitor",
"Gabriel",
"Pedro",
"Lorenzo",
"Lucas",
"Matheus",
"Enzo",
"Theo",
"Benjamin",
"Rafael",
"Nicolas",
"Guilherme",
"Gustavo",
"Samuel",
"Henrique",
"Felipe",
"Murilo",
"Joaquim",
"Joao Pedro",
"Joao Miguel",
"Enzo Gabriel",
"Daniel",
"Isaac",
"Pietro",
"Pedro Henrique",
"Lucca",
"Eduardo",
"Benicio",
"Leonardo",
"Vitor",
"Joao Lucas",
"Bryan",
"Joao",
"Caua",
"Davi Lucca",
"Anthony",
"Vicente",
"Vinicius",
"Caio",
"Antonio",
"Davi Lucas",
"Bento",
"Joao Gabriel",
"Joao Vitor",
"Noah",
"Francisco",
"Calebe",
"Gael",
"Emanuel",
"Ian",
"Luiz Miguel",
"Enrico",
"Thiago",
"Augusto",
"Otavio",
"Joao Guilherme",
"Ryan",
"Yuri",
"Levi",
"Vitor Hugo",
"Erick",
"Bruno",
"Nathan",
"Raul",
"Henry",
"Davi Luiz",
"Luiz Felipe",
"Thomas",
"Rodrigo",
"Davi Miguel",
"Andre",
"Fernando",
"Alexandre",
"Pedro Lucas",
"Breno",
"Arthur Miguel",
"Carlos Eduardo",
"Kaique",
"Yago",
"Kaue",
"Luan",
"Igor",
"Luiz Henrique",
"Luiz Gustavo",
"Arthur Gabriel",
"Mathias",
"Lucas Gabriel",
"Pedro Miguel",
"Arthur Henrique",
"Ruan",
"Tomas",
"Danilo",
"Enzo Miguel",
"Luiz Otavio",
"Ricardo",
"Oliver",
"Alice",
"Sophia",
"Laura",
"Valentina",
"Helena",
"Isabella",
"Manuela",
"Julia",
"Luiza",
"Livia",
"Giovanna",
"Maria Luiza",
"Heloisa",
"Maria Eduarda",
"Maria Clara",
"Lara",
"Lorena",
"Beatriz",
"Mariana",
"Melissa",
"Cecilia",
"Ana Clara",
"Ana Julia",
"Yasmin",
"Maria Julia",
"Isadora",
"Rafaela",
"Emanuelly",
"Ana Luiza",
"Esther",
"Lavinia",
"Sarah",
"Isabelly",
"Elisa",
"Eloah",
"Nicole",
"Maria Alice",
"Gabriela",
"Maria",
"Rebeca",
"Leticia",
"Clara",
"Marina",
"Isis",
"Ana",
"Alicia",
"Liz",
"Antonella",
"Maria Cecilia",
"Agatha",
"Catarina",
"Ana Laura",
"Larissa",
"Ana Beatriz",
"Maria Fernanda",
"Maite",
"Luna",
"Olivia",
"Vitoria",
"Bianca",
"Lais",
"Allana",
"Maria Valentina",
"Emilly",
"Ana Sophia",
"Clarice",
"Milena",
"Pietra",
"Fernanda",
"Carolina",
"Amanda",
"Maria Vitoria",
"Maria Helena",
"Eduarda",
"Malu",
"Maria Sophia",
"Stella",
"Camila",
"Maya",
"Gabrielly",
"Mirella",
"Mariah",
"Ana Livia",
"Maria Flor",
"Ayla",
"Isabel",
"Sophie",
"Giulia",
"Luana",
"Bruna",
"Ana Vitoria",
"Joana",
"Maria Laura",
"Maria Isis",
"Louise",
"Perola",
"Natalia",
"Ana Cecilia",
"Aurora",
"Barbara"
};

	//Fonte dos nomes: http://www.tiltedlogic.org/Familia/surnames.php
	char *sobre[] = {"Altoe",
"Sossai",
"Agrizzi",
"De Angeli",
"Ferreira",
"da Silva",
"Della Coletta",
"Zampirolli",
"Fernandes",
"Braga",
"Alves",
"Costalonga",
"Botteon",
"Caliman",
"de Oliveira",
"Zanette",
"Salvador",
"Silva",
"Pesca",
"Zandonadi",
"Tosi",
"da Costa",
"Gomes",
"Calmon",
"de Souza",
"Sossai detto Pegorer",
"de Almeida",
"Pereira",
"Falqueto",
"Martins"};
	
	srand( time(NULL) );                 // inicia o gerador randômico com a hora atual
	lista->f= 0;                         // cria nova lista
	int massa;                           // informa quantidade de dados a ser cadastrados
	printf("\n Cria nova lista. Defina a massa de dados [até 100]: ");
	do{
	   	fflush(stdin);
   	    scanf("%d", &massa);
   	}while( massa < 1 || massa > 100 );  // valida massa de dados entre 1 e 100
   	
	for( i= 0; i < massa; i++ ){         // laço para geração aleatória dos nomes e códigos
		 //lista->info[ i ].codigo = i + 1;// gerar código automático sequencial 
		 x = aleatorio( 199 );
	 	 strcpy( nomeTemp, nomes[ x ] ); // copia nome aleatório
		 strcat( nomeTemp, " ");         // espaço entre nome e sobrenome 
		 x = aleatorio( 29 );
		 strcat( nomeTemp, sobre[ x ] ); // concatena no nome o sobrenome aleatório
		 strcpy( lista->info[ i ].nome, nomeTemp );     // registra nome completo na lista	
		 lista->info[ i ].codigo = aleatorio( 199 ) + 1;// gerar código automático
	} // fim for ( i= 0; i < massa; i++ )
	lista->f = i;                        // atualiza controle de número de registros da lista
	printf( "\n Gerados [ %d ] registros. ", lista->f ); // informa número de registros gerados
}
