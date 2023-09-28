# Lambda Functions $\lambda$

### Aspectos Gerais do Cálculo Lambda

Considere a função $f: \mathbb{N}\to\mathbb{N}$ tal que:
$$f(x) = x + 1$$

É importante reparar que o que está sendo definido aqui não é a função f, mas a aplicação de f ao argumento **x**. Podemos dizer que f(x) = x + 1 não é uma função, mas uma equeção (pois x + 1 - f(x) = 0).

Podemos definir funções com mais rigor usando a **linguagem lambda**. Duas construções destacam-se na linguagem lambda: 

[1] _Abstração Lambda_. Permite abstrar a definição da função. Por exemplo, a função f é denotada pelo seguinte _termo lambda_ (elementos que definem ou representam funções na **linguagem lambda**):

$$\lambda x.(x + 1)$$
que pode ser interpretado como:

_função tal que, para um argumento arbitrário x resulta em x + 1_

[2] _Aplicação Lambda_. Determina o valor da função aplicada a um dado argumento. Por xemplo, a função f acima aplicada ao argumento 3 é denotada pelo seguinte termo Lambda:
$$(\lambda x.(x + 1))3$$
que pode ser interpretado como:
      
_aplicação da função $\lambda x.(x + 1)$ ao valor 3_

Assim, a notação Lambda permite a diferenciação da regra de associação (função) da aplicação da mesma em um argumento. Também, a notação deixa claro qual é o dado de entrada.

No caso de funções de _mais de uma variável_, tal função pode ser vista como uma função de uma váriavel quando se **fixa** um dos parâmetros. Por exemplo, para a função de adição, fixando o segundo argumento no valor 1, obtém-se a função sucessor $\lambda x.(x + 1)$. O mesmo raciocínio permite construir as funções correspondetes às regras $x \mapsto x + 1, \quad x \mapsto x + 2, \quad x \mapsto x + 3...$ Generalizando este raciocínio, a adição pode ser representada pelo seguinte **termo lambda**:
$$\lambda y.( \lambda x.(x + y))$$

Dessa forma, somente com **abstração lambda e aplicação lambda** é possível representar funções com qualquer número de variáveis.

Em resumo, o cálculo Lambda é a linguagem Lambda jutamente com um conjunto de axiomas e regras que permite inferer quando dois termos Lamdas denotam a mesma função.

### Linguagem Lambda

Uma _Linguagem Lambda_ é o conjunto dos termos Lambdas sobre um conjunto de váriaveis.

**Definição**: Termo Lambda

Seja **V** um conjunto infinito e enumerável de variáveis. Então um _termo lambda_, $\lambda - termo$, _expressão lambda_ ou _palavra lambda_ sobre **V** é indutivamente definido como segue:

1. _Variável_. $x \in V$ e é um $\lambda -termo$;
2. _Abstração Lambda_ ou $\lambda -abstracao$. Se **M** é um $\lambda - termo$ e $x \in V$, então também é um $\lambda -termo$:
$$(\lambda x.M)$$

3. _Aplicação Lambda_ ou $\lambda - aplicacao$. Se **M** e **N** são $\lambda -termos$, então também são $\lambda - termos$:
$$(M \quad N)$$

Intuitivamente temos a definição de um $\lambda - termo$:
* abstração Lambda representa a operação de conceder cárater funcional à um objeto. Assim $\lambda x.(M)$ representa uma função que possui um parâmetro de entrada; 
* aplicação Lambda (M N) representação a aplicação de uma função M à um objeto (entrada) N

exemplos de termos lambdas (os numeros mapeam para as definições acima)

$x \quad  1$

$\lambda x.x \quad 1, 2$

$(x y) \quad 1, 3$

$(\lambda x.x \lambda x.x) \quad 1, 2, 3$

**Definição**: Linguagem Lambda

Seja **V** um conjunto infinito de variáveis, uma linguagem lambda, ou $\lambda -linguagem$, é o conjunto de todos os $\lambda - termos$ sobre esse conjuntos. 


