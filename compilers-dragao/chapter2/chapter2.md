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

### Tabela de simbolos

_Tabelas de Simbolos_ são estruturas de dados usadas pelos compiladores para conter informações sobre as construções do programa fonte. Ela é construída de forma incrimental durante as fases de analise e usada pelas fases de síntese para gerar o cógido objeto. As entradas da tabela conterão informações sobre um identificador, como seu nome ou lexema, seu tipo, seu endereço na memoria e qualquer outra informação relevante.

Um bloco de programa terá sua própria tabela de simbolos, sendo as declarações neste blocos as entradas.

Uma tabela de simbolos por escopo pode ser definida da seguinte forma:

A _regra de aninhamento mais interno_ para blocos é que um identificador x está no escopo da declaração aninhada mais interna de x, ou seja, a declaração de x é encontrada examinando os escopos de dentro pra fora, começando com o bloco que x aparece.

A regra de aninhamento mais interno pode ser implementada encadeando tabelas, de modo que a tabela mais aninhada possua acesso à tabela anterior.

Um exemplo da implementação pode ser encontrada nos códigos da seção 2.7.

### Código de três endereços

O código de três endereços é uma sequência de instruções no formato `x = y op z`, onde x, y e z são nomes, restrições ou temporários gerados pelo compilador; e **op** significa operador.

Os arranjos são tratados da seguinte forma;

```
x [ y ] = z

x = y [ z ]
```

As instruções de três endereços são executadas de forma sequencial, a não ser que sejam forçadas por um desvio condicional ou incondicional:

```
ifFalse x then goto L
ifTrue x then goto L
goto L
```

E, finalmente, uma instrução para copiar um valor: `x = y`

O seguinte leiaute ilustra a o comando `if expr then stmt`

`ifFalse x goto _after_`

```
código para calcular
      expr em x
------------------------
ifFalse x goto after
------------------------
código para stmt
------------------------
after:
```

O pseudocódigo para a classe _If_:

```java
class If extends Stmt {
  private Expr e;
  private Stmt s;
  private String after;

  public If( Expr x, Stmt y ) {
    this.E = x;
    this.S = y;
    after = newLabel();
  }

  public void gen() {
    Expr n = e.rvalue();
    emit("ifFalse " + n.toString() + "goto " + after);
    S.gen();
    emit(after + ":");
  }
}
```

Foi falado sobre a tradução de comandos, agora falaremos sobre a tradução de expressões contendo operadores binários op, acessos a arranjos e atribuições, além de constantes e identificadores.

Usaremos a técnica simples de gerar uma instrução de três endereços para cada nó operador para expressões. Nenhum código é gerado para constantes e identificadores, pois eles podem aparecer como endereços nas instruções.

Se um nó _x_ da classe _Expr_ tiver operador op, então uma instrução é emitida para calcular o valor no nó _x_ para um nome "temporário" gerado pelo compilador, digamos, _t_.

Exemplo:

```
Para i-j+k teremos,

t1 = i - j
t2 = t1 + k
```

Com os acessos a arranjos e atribuições, é necessário distinguir entre _r-values_ e _l-values_. Por exemplo:

```
2*a[i] pode ser traduzido calculando o r-value de a[i]

t1 = a [ i ]
t2 = 2*t1
```

Porém não podemos usar um temporário para `a[i]` se ele aparecer no lado esquerdo.
A técnica mais simples é usar as funções `lvalue` e `rvalue`. Quando a função `rvalue` é aplicada a um nó não folha de _x_, ela gera instruções para calcular _x_ em um "temporário" e retorna o endereço do temporário. Quando aplicada à um `lvalue` ela também gera instruções para calcular as subárvores abaixo de _x_ e retorna um nó representado pelo "endereço" de _x_.

```
Expr lvalue(x: Expr) {
  ir (x é um nó Id) return x;
  else if (x é um nó Access(y, z) e y é um nó Id) {
    return new Access(y, rvalue(z));
  }
  else error;
}
```

```
Expr rvalue(x: Expr) {
  if (x é um Id ou um nó Constant) return x;
  else if (x é um nó Op(op, y, z) ou um nó Rel(op, y, z)) {
    t = novo temporário;
    emite string para t = rvalue(y) op rvalue(z);
    return um novo nó para t;
  } else if (x é um nó Access(y, z)){
    t = novo temporário;
    call lvalue(x), que retorna Access(y, z');
    emite string para t = Access(y, z');
    return um novo nó para t;
  } else if (x é um nó Assign(y, z)) {
    z' = rvalue(z);
    emite string para lvalue(y) = z';
    return z';
  }
}
```

```
exercício 2.8.1

for ( expr1; expr2 ; expr3 ) stmt;

expr1; while ( expr2 ) { stmt expr3 };

leiaute:

----------------------

código para calcular
  expr1 em x

----------------------

loop:
  código para calcular
    expr2 em y usando x

  ifFalse y goto stop

----------------------

stmt

----------------------

código para calcular
  expr3 em x

goto loop

----------------------

stop:

----------------------


pseudocódigo:

class For extends Stmt {
  Expr e1;
  Expr e2;
  Expr e3;
  Stmt s;
  String stop;
  String loop;

  public For(Expr x, Expr y, Expr z, Stmt st) {
    e1 = x;
    e2 = y;
    e3 = z;
    s = st;
    stop = newLabel();
    loop = newLabel();
  }

  public void gen() {
    Expr n1 = e1.rvalue();

    emit(loop + ":");

    Expr n2 = e2.rvalue();

    emit("ifFalse " + n2.toString() + " goto " + stop);

    S.gen();

    Expr n3 = e3.rvalue();

    emit(n3.toString());

    emit("goto " + loop)

    emit(stop + ":")
  }

}

exercício 2.8.2:

class If extends Stmt {
  Expr E;
  Stmt S;
  String after;

  public If( Expr x, Stmt y ) {
    E = x;
    S = y;

    after = newLabel();
  }

  public gen() {
    Expr n = E.rvalue();
    emit("ifZero " n.toString(); " goto " + after);
    S.gen();
    emit(after + ":");
  }
}

```