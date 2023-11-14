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

### Exercicios

2.2.1) Considere a gramática livre de conteto
$$S \to S \, S\, + \quad | \quad S \, S \, * \quad |\quad a$$

a) Mostre que a cadeia "aa+a*" pode ser gerada por essa gramatica:

vamos começar pelo primeiro "a":

a é S pois $S \to a$

logo, "a a +" é S pos $S \to S \, S \, +$

por fim, "a a + a *" é S pois

$S \to S \, S \, *$

b) Construa uma árvore de derivação para essa cadeia
```
          S
      /   |   \
     /    |    \
    /     |     \
    S     S      *
  / | \   |
 S  S  +  a
 |  |
 a  a
```

c) Gramática para as operações de multiplicação e adição em notação pós-fixada, pois define a regra onde para as operações binárias de soma ou multiplicação seus operandos são especificados antes.

2.2.2) que linguagem é gerada pelas gramática a seguir?

a) $S \to 0 \; S \; 1 \quad | \quad 0 \; 1$

0 1

0 0 1 1

0 0 0 1 1 1

0 0 0 0 1 1 1 1

A linguagem de duplo balanceamento entre 0's e 1's, onde

$\{ \; 0^n \; 1^n \quad | \quad n \ge 0\; \}$

b) $S \to + SS | - SS | a$

linguagem de soma e subtração do algarismo "a" em notação infixada

c) $S \to S (S) S | e$

e (e) e

e (e) e (e) e

e (e) e (e (e) e) e (e) e

numero arbitrário de e's com parenteses fechados, podendo estar aninhados.

d) $S \to a S b S | b S a S | e$

a e b e

a a e b e b a e b e

a a a e b e b a e b e b a a e b e b a e b e

mesmo numero de a's e b's e "e"+1

e) $S \to a|S+S|SS|S*|(S)$

https://en.wikipedia.org/wiki/Regular_expression

A regular expression used to express regular languages

dado um alfabeto $\Sigma$:

* literal character: a in $\Sigma$

* concatenation: S+S

* Kleene star: S*

* Alternation: SS

2.2.3) Quais gramaticas do exercicio anterior sao ambiguas?

a) não

b) não

c) sim:

e (e) e (e) e


### atributos

atributos podem ser qualquer valor associado a uma construção de programa.
Como usamos símbolos de gramática para representar as construções dos nosso programas,
estendemos a noção dos atributos das construções aos símbolos que eles representam.

### Esquemas de tradução (dirigidos por sintaxe)
É uma notação para contectar fragmentos de programa às produções de uma gramática

### Notação pós-fixada

1. se E é uma variavel ou constante, então a notação pós-fixada de E é o próprio E
2. Se E é uma expr no formato E1 op E2 onde op é uma operação binária, então a notação para E será E1'E2' op, onde E1' e E2' são as notações pós-fixadas de E1 e E2 respectivamente
3. Se E é uma expr entre parenteses da forma (E1) então a notação pós-fixada para E é a mesma que para E1

### Árvore de Sintaxe

Um ponto de partida útil para iniciar o projeto de um tradutor é uma estrutura de dados chamada árvore de sintaxe abstrata.
Em uma árvore sintática abstrata, para uma expressão, cada nó interior representa um operador; os filhos do nó representam
os operandos do operador.

9-5+2:

     +
    / \
   -  2
 /  \
9    5

Árvores sintáticas são, até certo ponto, parecidas com árvores de derivação. Porém, na árvore sintática, os nós interiores representam
construções de programação, enquanto na árvore de derivação os nós interiores representam não-terminais. Muitos dos não-terminais de uma
gramática representam construções de programação, mas outros são "auxiliares" (como digitos ou termos usados nos exemplos anteriores).
Na árvore sintática estes não-terminais auxiliares são removidos.

### Análise Léxica

Um analisador léxico lê os caracteres de entrada e os agrupa em "objetos tipo token". Junto com o símbolo terminal que é usado durante a análise sintática, um
objeto token carrega informações adicionais na forma de valores de atributo.

Uma sequencia de caracteres de entrada compreendendo um único token é chamada de _lexema_. Assim, podemos dizer que o analisador léxico isola do analisador sintático
a representação do lexema dos tokens.

Analisador léxico da seção 2.6