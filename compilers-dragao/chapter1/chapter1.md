## Chapter 1 - Introduction

1.1.1)  Compiladores produzem como saída um programa executável, já um interpretador executa o programa diretamente.

1.1.2) O programa produzido por um compilador processa mais rapidamente as entradas para as saídas. Porém, um interpretador oferece um melhor diagnóstico dos problemas de erros.

1.1.3) A linguagem simbólica pode ser mais fácil de ser gerada e depurada do que a linguagem de máquina

1.1.4) C é uma linguagem simples, mas poderosa. As razões de utiliza-lá como linguagem objeto são muitas, como facilidade na depuração, facilidade na geração do código. Além do mais, existem vários compiladores de C que compilam para quase qualquer tipo de hardware. 

1.1.5) Produz machine code.

## Estrutura de um Compilador

Análise: subdivide o programa em partes constituintes e impõe uma estrutura gramatical sobre elas. Depois, utiliza dessa estrutura para gerar um código intermediário. Se o programa estiver mal formato semanticamente, o compilador deve emitir uma mensagem de erro.

Síntese: constrói o programa objeto a partir da linguagem intermediária gerada na fase de análise.

### Análise Léxica

A primeira fase do compilador é a análise léxica. Nela, o analisador léxico lê a sequencia de caracteres que compõe o programa e os agrupa em sequência significativas chamadas `lexemas`. Para cada lexema o analisador léxico produz como saída um token no formato `<nome-token, valor-atributo>`. O nome do token é um nome abstrato que damos ao token e o valor atributo aponta para uma entrada na tabela de símbolos.

### Análise Sintática 

O analisador sintático utiliza o primeiro valor dos tokens para produzir uma representação intermediária tipo árvore, que mostra a estrutura gramatical da sequência de tokens. Uma representação típica é a de `árvore de sintaxe`, em que cada operação é um nó na árvore e seus filhos são os arguments.

### Análise Semântica

O analisador semântico utiliza a árvore de sintaxe e as informações da tabelas de símbolos para verificar a consistência da semântica do programa com a definição da linguagem. Além disso, o analisador semântico reúne informações sobre os tipos e as salva na árvore de sintaxe ou na tabela de símbolos para uso subsequente.

### Geração de Código Intermediário 

Depois da análise sintática e semântica do programa fonte, muitos compiladores geram uma representação intermediária explícita de baixo nível ou do tipo de linguagem de máquina. Essa representação deve ser facilmente produzida e facilmente traduzida para a máquina alvo.

### Otimização de Código

A fase de otimização de código independe de máquina busca modificar o código intermediário a fim de otimiza-lo. Normalmente isso significa deixa-lo mais rápido, mas é possível fazer otimizações como de energia ou simplesmente 
diminuir a quantidade de código gerado.

### Geração de Código

O gerador de código recebe como entrada um programa intermediário e o mapeia em linguagem objeto.






