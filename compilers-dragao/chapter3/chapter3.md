### Análise Léxica

Como a primeira fase de um compilador, a tarefa principal do analisador léxico é ler a entrada de dados do programa fonte, agrupá-los em lexemas e produzir como saída uma sequência de tokens para cada lexema. O fluxo de tokens é enviado para o analisador sintático.

Normalmente, a interação entre analisador sintático e analisador léxico é implementada na forma de `getNextToken()`, chamado pelo analisador sintático.
Essa interação pode ser representada como:


```
Analisador -------token------> Analisador
   Léxico  <---getNextToken--- Sintático
        \                    /
         \                  /
         tabela de simbolos
```

Como o analisador é a parte do compilador que lê o código fonte, ele pode fazer outras tarefas, como expansão de macros, remoção de comentários, remoção de espaços em branco...

Além de poder manter a posição das linhas para localizar erros.

### Token, Padrões e Lexemas

* Um _token_ é um par consistindo de um nome e um valor de atributo opcional. O nome do token é um símbolo abstrato que representa um tipo de unidade léxica, por exemplo, uma palavra-chave.
* Um _padrão_ é um descrição da forma que os lexemas de um token podem assumir. No caso de palavras-chave, o padrão é a sequência de caracteres que forma a palavra-chave. Para identificadores e alguns outros tokens, o padrão poderá ser uma estrutura mais complexa, que é _casada_ por muitas sequências de caracteres.
* Um _lexema_ é uma sequência de caracteres no programa fonte que casa com o padrão o padrão para um token e é identificado pelo analisador léxico como uma instância desse token.

`printf("ola mundo")`

printf é um lexema casando com o padrão para o token Id e "olá mundo" casa com o padrão literal.

token = (literal, "ola mundo")
token = (id, "printf")

Em muitas linguagens de programação, as classes a seguir abrangem a maioria, senão todos os tokens:

1. Um token para cada palavra-chave. O padrão para a palavra-chave é a própria palavra-chave.
2. Tokens para operadores, seja individualmente ou em classes, como o token `comparison`
3. Um token representando todos os identificadores.
4. Um ou mais tokens para constantes, como números e strings.
5. Tokens para cada simbolo de pontuação, como parenteses esquerdo e direito, virgula e ponto-e-virgulas.

### Atributos de tokens

Quando mais de um lexema casar com um padrão, o analisador léxico precisas enviar mais informações para as fases subsequentes do compilador. Por exemplo, os lexemas 1 e 0 casam com o padrão **number**, mas é importante pro compilador saber qual lexema foi usado.

Um exemplo importante é o do token **id**. Um token do tipo id pode ter muitas informações e, normalmente, essas informações ficam mantidas na tabela de símbolos. Logo, um valor apropriado para um token id é um apontador para a sua entrada na tabela de símbolos.

```
exercício 3.1

float limitedSquare(x) float x {
    return (x <=-10.0 || x>= 10.0) ? 100 : x*x;
}

<typedef, float>
<id, *table.find(limitedSquare)>
<(>
<id, *table.find(x)>
<)>
<typedef, float>
<id, *table.find(x)>
<{>
<return>
<(>
<id, *table.find(x)>
<rel, <=>
<number, -10.0>
<bool_op, ||>
<id, *table.find(x)>
<rel, >=>
<)>
<op, ?>
<number, 100>
<op, :>
<id, *table.find(x)>
<mult>
<id, *table.find(x)>
<;>
<}>

3.1.2

Tudo que estiver fora de <></> é tratado como TEXT

Quando uma tag for aberta, o token TAG é produzido


TOKEN_TAG, "a"

com tags abertas, podemos diferenciar
identificadores como HREF = "..."

```
### Especificação de Tokens

As expressões regulares são de extrema importância para identificação de tokens. Embora não podemos identificar todos os padrões com elas, ela são muitos eficientes para identificar os padrões que realmente precisamo

Termos para partes de uma cadeia caracteres:

1. Prefixo: qualquer cadeia obtida pela remoção de zero ou mais símbolos do final
2. pós-fixada: qualquer cadeia obtida pela remoção de zero ou mais símbolos do começo
3. Subcadeia: qualquer cadeia dentro da sequencia
4. Os _próprios_, que podem ser os anteriores, mas sem a palavra vazia e a própria cadeia
5. subsequencias: qualquer combinação obtida removendo zero ou mais posições não necessariamente consecutivas

**Operações sobre linguagens**

União, concatenação, fecho de Kleene e fechamento positivo.

O fecho de kleene pode ser identificado como

L* = zero ou mais vezes L
L+ = uma ou mais vezes L

**Expressões regulares**

Expressões regulares é a notação dada ao conjunto de todas as linguagens que podem ser formadas com as operações acima aplicadas aos símbolos de algum alfabeto.

Nesta notação, poderimos ter a seguinte expressão para representar identificadores na linguagem C:
letra_ (letra_ | digito_)*

onde letra_ é uma letra ou _ e digito_ é um digito ou _.

**Definições Regulares**

Por conveniência de notação, podemos dar nomes a certas expressões regulares e usar seus nomes em expressões subsequentes.

Exemplo dos identificadores em C:

letter_ -> A | B | ... | Z | a | b | ... | z | _
digit -> 0 | 1 | 2 | ... | 9
id -> letter_ (letter_ | digit)*

**Extensões de Expressões Regulares**

Desde que Kleene criou as expressões regulares com os operadores básico para união, concatenação e fecho de _kleene_, na década de 1950, muitas extensões foram acrescentadas.

1. _Uma ou mais instâncias_. O operador unário pós-fixado + representa o fechamento positivo de uma expressão regular e sua linguagem. O operador + tem a mesma precedencia do *.
2. _Zero ou uma instância_. O operador pós-fixado ?, r? representa r|e. Possui a mesma precedencia de * e +
3. _Classes de caracteres_. Representado por [a1...an] onde a é uma sequencia lógica.

letter_ -> [A-Za-z-]
digit -> [0-9]
