## Analise léxica

O papel do analisador léxico é, sobretudo, construir a AST a partir dos tokens gerados pelo analisador léxico.
Porém, mais do que isso, o analisador léxico poderá ser responsável por outra tarefas, como a identificação de
erros do programador.

Existem três estratégias gerais para a análise léxica: Universal, descendente e ascendente.
O métodos baseados em estratégias universais, como o do algoritmo de Cocke-Younger-Kasami e o de Earley são ineficientes.
Normalmente, em compiladores de produção, são utilizadas as demais estratégias.

Erros em programas aparecem nas seguintes formas:
* Erros léxicos: escrever o nome de uma variável de forma incorreta, como `getEllipse` -> `getElipse`. Ou o esquecimento de fechar as `"` em uma _String_;
* Erros sintáticos: `;` mal colocados, parênteses|chaves|colchetes não balanceados, etc;
* Erros semânticos: mismatch de operadores e operandos. Como em `"123" - 1`, onde temos um operador `-`, que espera `number op number`;
* Erros lógicos: constituem erros como o uso de uma atribuição onde uma comparação seria o correto. O programa pode estar bem formado, mas não reflete a intenção do programador. `while ( running = true ) ;` =/= `while ( running == true ) ;`

Tipos de Recuperação de Erros:

* Modo pânico: ao detectar um erro, o analisador sintático descartará um token por vez, até achar um token de "sincronismo". Tokens de sincronismo são não ambuiguos e possuem um papel claro.
* Recuperação de nível de frase: retirar `;` ou adicionar `;` conforme necessário, por exemplo. É necessário ter cuidado para não entrar em loops infinitos.
* Produções de erros: estende-se a gramática com produções que representam os erros comuns da linguagem.
 
## Gramáticas Representativas

As construções sintáticas como `while` e `int`, são relativamente mais fáceis de serem analisadas, pois a palavra chave guiará na escolha de produção.
Expressões que podem ser mais desafiadores de serem analisadas envolvem precedência e associatividade.

Associatividade e precedência podem ser capturadas na gramática a seguir.

$E \to E + T | T$

$T \to E*F| F$

$F \to (E)| id$

Tal gramática pertence a classe LR (left to right), que são adequadas para a análise sintática ascendente. A gramática pode ser adaptada para incorporar novos operadores e novos níveis de precedência. No entanto, ela não pode ser usada com o método de análise descendente, pois é recursiva à esquerda.

Uma variação sem recursão à esquerda será usada para análise descendente:

$E \to TE'$

$E' \to + T E' | e$

$T \to F T'$

$T' \to * F T' | e$

$f \to (E) | id$

