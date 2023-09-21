# Funções Recursivas Parciais ou Funções Recursivas de Kleene

Referencias: 
- Teoria da Computação: máquinas universais e computabilidade - Cap 8. Diverio, Menezes
- [Playlist Youtube](https://www.youtube.com/playlist?list=PLfOnKvd6pFirXDbgF4OeZDTfRnMj4B-QL)

Kleene: 

![Kleene](https://upload.wikimedia.org/wikipedia/commons/thumb/1/1c/Kleene.jpg/200px-Kleene.jpg)

São funções contruídas sobre três funções naturais básicas:
* natural zero visto como função - $f(x) = 0$

* sucessor (de um número natural) - $f(x) = x + 1$
* projeção - $u²_2(1, 2)=2$

juntamente com as seguintes operações 
* substuição composicional
* recursão
* minimização 

constituindo uma forma compacta e natural para definir muitas funções e suficientemente poderosa para descrever toda função intuitivamente computável.
* uma função é **Turing-computável** se, e somente se, a função é **recursiva parcial**
* uma função é **Turing-computável** por uma máquina que sempre **para** se, e somente se, a função é recursiva total (é definida para todo e qualquer valor de entrada)

### Substitução Composicional 

Queremos combinar funções computável, fazendo assim com que a saída de uma seja a entrada de outra, como: 

$h(x) = f(g(x))$

Por exemplo,

$f(x) = 2*x \quad e \quad  g(x) = x + 1$

temos que, para $x = 2$ :

$h(2) = f(g(2))$

$h(2) = f(2 + 1)$

$h(2) = 2(3)$

$h(2) = 6$


definição - Substitução Composicional (para n argumentos)

sejam as funções parciais:

$g: \mathbb{N^k} \to \mathbb{N} \quad e \quad f_1, f_2, ..., f_k: \mathbb{N^n} \to \mathbb{N}$

A função parcial 

$g: \mathbb{N^n} \to \mathbb{N}$

é a substituição composicional de funções, ou simplesmente substituição de funções, definida a partir de $g, f_1,  f_2, ..., f_k$ como segue:

$h(x_1, x_2, ..., x_n) = g(f_1(x_1, x_2, ..., x_n), f_2(x_1, x_2, ..., x_n), ..., f_k(x_1, x_2, ..., x_n))$

Ou seja, a substituição generaliza a composição usual de funções, construindo h a partir da substituições dos $y_i$ (entradas) em $g(y_1, y_2, ..., y_k)$ pelos correspondentes $f_i(x_1, x_2, ..., x_n)$

**definição - Recursão Primitiva**

sejam 

$f: \mathbb{N^n}\to\mathbb{N}\quad e \quad g:\mathbb{N^{n+2}}$

a função parcial:

$h:\mathbb{N^{n+1}} \to  \mathbb{N}$

é definida por _recursão primitiva_ a partir de f e g como segue:

$h(x_1, x_2, ..., x_n, 0) = f(x_1, x_2, ..., x_n)$ _BASE_

$h(x_1, x_2, ..., x_n, y + 1) = g(x_1, x_2, ..., x_n, y, h(x_1, x_2, ..., x_n, y))$ _RECURSAO_ 

**definição - Minimização**

O conceito de minimização que segue não é intuitivo na noção de funções recursivais parciais.
Isso se dá por que, em caso de funções parciais, pode haver situações onde a minimização não produzirá um resultado válido, pois a função não estará definida para tal entrada. 

seja 

$f:\mathbb{N^{n+1}}\to\mathbb{N}$

uma função parcial. A função parcial:

$h:\mathbb{N^n}\to\mathbb{N}$

é dita definida por _minimização_ de f e é tal que, $\forall(x_1, x_2, ..., x_n, y) \in  \mathbb{N}$

$h(x_1, x_2, ..., x_n) = min\{y | f(x_1, ..., x_n, y) = 0\}$

A minização é um dos conceitos fundamentais para a construção de funções recursivas. Ela é frequentemente usada para encontrar o menor valor para uma função onde o predicado é verdade.

Por exemplo, dada a função:

$f(x, n) = 0$

podemos usar a minização para encontrar o menor valor de $n$ para que o predicado seja verdade.

Podemo começar com $n = 0$ e incrementar... 





