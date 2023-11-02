## Chapter 2 - Tradutor simples dirigido por sintaxe

Nesse capitulo será introduzido técnicas de compilação que serão aprofundadas nos capitulos 3 a 6. Essas técnicas serão ilustradas com o desenvolvimento de um programa em Java (eu vou fazer em C) completo que traduz instruções de uma linguagem representativa para código de três endereços, representação intermediária. 

Começamos criando um tradutor dirigido por sintaxe que mapeia expressões artiméticas infixadas em expressões posfixadas. 

## Definição da Sintaxe

Uma gramatica descreve naturalmene a estrutura hierárquica da maiora das construções de linguagens de programação.

if (_expression_) _statement_ else _statement_

Ou seja, um comando if-else é a concatenação da palavra-chave **if**, um parêtense de abertura, uma expressão, um parêntese de fechamento, um comando, a palavra-chave **else** e outro comando. Podemos expressão essa regra de construção como:

_stmt_ -> **if** ( _exp_ ) _stmt_ else _stmt_ 

onde a seta pode ser lida como "pode ter a forma". Essa regra é chamada de _produção_. Em uma produção, os elementos léxicos como a palavra-chave **if** e os parênteses são chamados de _terminais_. Variáveis como _expr_ e _stmt_ representam sequencias de terminais e são chamados de _não-terminais_.

>**_Tokens:_** Por motivos descritos no livro, na discussão sobre análise sintática, normalmente nos referimos aos tokens e aos terminais como sinônimos

### Definição de Gramáticas

Uma _gramática livre de contexto_ possui quatro componentes:

1. Um conjunto de símbolos _terminais_, às vezes chamado de tokens. São os simbolos elementares da linguagem;
2. Um conjunto de _não-terminais_, às vezes chamados de varaveis sintáticas. São sequencias de símbolos terminais que descrevemos;
3. Um conjunto de _produção_, em cada produção consiste em um não-terminal, chamado de _cabeça_ ou _lado esquerdo_ da produção, uma seta e uma sequencia de terminais e/ou não-terminais, chamados de _corpo_ ou _lado direito_;
4. Uma designação de um dos não-terminais como o símbolo inicial da gramática. 

Definimos uma gramática listando suas produções. Varias produções podem ser agrupadas se possuírem a mesma cabeça, separados por **|** que lemos como "ou":

_Listas de digitos separadas por sinais de adição ou subtração_:

$list \to list + digit \quad (1)$

$list \to list - digit \quad (2)$

$list \to digit \quad (3)$

$digit \to 0|1|2|3|4|5|6|7|8|9 \quad (4)$

podemos escrever o corpo das três produções como:

$list \to list + digit | list - digit | digit$

### Derivações

Uma gramática deriva cadeias começando com o símbolo inicial e substituindo repetidamente um não-terminal pelo corpo de uma produção para esse não terminal. Por exemplo:

Podemos deduzir que 9 - 5 + 2 é uma lista pois:

1. 9 é uma _list_ pela produção **(3)**, pois 9 é um _digit_;
2. 9 - 5 é uma _list_ pela produção **(2)** pois 9 é uma _list_ e 5 é um _digit_;
3. 9 - 5 + 2 é uma _list_ pela produção **(1)** pois 9 - 5 é uma _list_ e 2 é um _digit_.

A análise sintática consiste em, a partir de uma cadeia de terminais, tentar descobrir como derivá-la a partir do simbolo inicial da gramática e, se não for possível, informar os error de sintaxe.


