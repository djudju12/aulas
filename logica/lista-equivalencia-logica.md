### 1

a)

p ^ (p v q) <=> p

| p  | q  | p ^ (p v q)  | p|
|-   |-   |-             | -|
| 1  | 1  | 1            | 1|
| 1  | 0  | 1            | 1|
| 0  | 1  | 0            | 0|
| 0  | 0  | 0            | 0|

b)

p v (p ^ q) <=> p

| p  | q  | p v (p ^ q)  |p|
| -  | -  | -            |-|
| 1  | 1  | 1            |1|
| 1  | 0  | 1            |1|
| 0  | 1  | 0            |0|
| 0  | 0  | 0            |0|

c)

(p -> q) v (p -> r) <=> p -> (p v r)

| p  | q  | r  | (p -> q) v (p -> r)  |p -> (p v r) |
| -  | -  | -  | -                    |-            |
| 1  | 1  | 1  | 1                    |1            |
| 1  | 1  | 0  | 1                    |1            |
| 1  | 0  | 1  | 1                    |1            |
| 1  | 0  | 0  | 0                    |1            |
| 0  | 1  | 1  | 1                    |1            |
| 0  | 1  | 0  | 1                    |1            |
| 0  | 0  | 1  | 1                    |1            |
| 0  | 0  | 0  | 1                    |1            |

Não há equivalência lógica

d)

p + q <=> (p v q) ^ ~(p ^ q)

| p  | q  | p + q  |(p v q) ^ ~(p ^ q) |
| -  | -  | -      |-                  |
| 1  | 1  | 0      |0                  |
| 1  | 0  | 1      |1                  |
| 0  | 1  | 1      |1                  |
| 0  | 0  | 0      |0                  |

e)

(p <-> q) v (p -> r) <=> (p -> q) v r

| p  | q  | r  | (p -> q) v r  | (p <-> q) v (p -> r) |
| -  | -  | -  | -             | -                    |
| 1  | 1  | 1  | 1             |1                     |
| 1  | 1  | 0  | 1             |1                     |
| 1  | 0  | 1  | 1             |1                     |
| 1  | 0  | 0  | 0             |0                     |
| 0  | 1  | 1  | 1             |1                     |
| 0  | 1  | 0  | 1             |1                     |
| 0  | 0  | 1  | 1             |1                     |
| 0  | 0  | 0  | 1             |1                     |

### 2

Não é verdade que Pedro é pobre e Alberto é alto

~(p ^ q) <=> ~p v ~q

Não é verdade que Pedro é pobre ou Não é verdade que Alberto é alto

### 3

Não é verdade que Se Pedro é pobre então Alberto é alto
```

~(p -> q)

p ^ ~q
```

### 4

Não é verdade que Pedro é pobre sse Alberto é alto
```
~(p <-> q)
p + q

Pedro é pobre e não é verdade que Alberto é alto
```

### 5

Algum carro é veloz

Nenhum carro é veloz

### 6

Algum livro não é ilustrado

Todo o livro é ilustrado

### 7

a) (X ^ Y)      = ~(X ^ Y) = ~X v ~Y

b) (~X ^ Y)     = ~(~X ^ Y) = X v ~Y

c) (~X ^ ~Y)    = X v Y

d) (X v Y)      = ~(X v Y) = ~X ^ ~Y

e) (~X v Y)     = X ^ ~Y

f) (~X v ~Y)    = X ^ Y

g) (X -> Y)     = ~(X -> Y) = X ^ ~Y

h) (~X -> Y)    = ~(~X -> Y) = ~X ^ ~Y

i) (~X -> ~Y)   = ~X ^ Y

j) (X <-> Y )   = ~(X <-> Y) = X + Y

k) (~X <-> Y )  = ~X + Y

### 8

a) A contrapositiva de (p -> ~q)
```
~q -> p
q -> ~p
```

b) A contrária da contrapostiva de [(~p -> q) -> (~p v q)]
```
~(~p v q) -> ~(~p -> q)    | contrapositiva
~~(~p v q) -> ~~(~p -> q)  | contrária
(~p v q) -> (~p -> q)      | simplificacao
```



c) A recíproca da contrapositiva da contrária de [(p -> ~q) ->q]
```
~(p -> ~q) -> ~q   | contrária
~~q -> ~~(p -> ~q) | contrapositiva
~~(p -> ~q) -> ~~q | recíproca
~(p -> ~q) -> ~q   | simplificacao
```


d) A recíproca da contrapositiva de {[(~p ^ ~q) -> q] -> p}
```
~p -> ~[(~p ^ ~q) -> q] | contrapositiva
~[(~p ^ ~q) -> q] -> ~p | recíproca
```

### 9

a) Pedro não é arquiteto ou Paulo é programador.
```
p = Pedro é arquiteto
q = Paulo é programador

~p v q
q v ~p | comutativa
```

b) João é programador sse Lucas é artista
```
p = João é programador
q = Lucas é artista

p <-> q
q <-> p | comutativa
```

c) Paulo e Lucas são desenvolvedores
```
p = Paulo é desenvolvedor
q = Lucas é desenvolvedor

p ^ q
q ^ p | comutativa
```

d) Paulo ou Lucas ou João são desenvolvedores.
```
p = Paulo é desenvolvedor
q = Lucas é desenvolvedor
r = João é desenvolvedor

p v q v r
p v (q v r) | associativa
```


### 10
a)
```
(p->q) v (p v q) | original

(p v q) v (p->q) | comutativa

(~p v q) v (p v q) | condicional

(p->q) v (~p -> q) | condicional
```

b)
```
(p <-> q) v (~(p ^ q) -> r) | original

(p <-> q) v ((p ^ q) v r) | condicional

(q <-> p) v (~(p ^ q) -> r) | comutativa

((p v q) ^ (~p v ~q) ) v (~(p ^ q) -> r) | bicondicional
```

### 12

a) O tempo será frio e chuvoso.
```
~(p ^ q)
~p v ~q

O tempo não será frio ou não será chuvoso
```

b) Ele cometeu um erro ou não foi responsável.
```
~(p v ~q)
~p ^ q

Ele não cometeu um erro e foi responsável
```

c) Marina não é morena ou Ana é baixa.
```
~(~p v q)
p ^ ~q

Marina é morena e Ana não é baixa
```

d) Se o tempo está chuvoso então está frio.
```
~(p -> q)

p ^ ~q

O tempo está chuvoso e não está frio
```

e) Todos os corvos são negros.
```
Alguns corvos não são negros
```

f) Nenhum triângulo é retângulo.
```
Algum triângulo é retângulo
```

g) Alguns sapos são bonitos.
```
Nenhum sapo é bonito
```

h) Algumas vidas não são importantes
```
Todas as vidas são importantes
```

### 13

Verifique se as proposições abaixo são equivalentes, referenciando as regras de equivalência
utilizadas.
a)
```
r v r <=> r
3 - Idem potente
```

b)
```
p -> ~q <=> ~(p ^ q) | original

~(p ^ q) <=> ~p v ~q | 1° lei de morgan

p -> ~q <=> ~p v ~q
1 - condicional
```

c)
```
~p ^ (q v r) <=> (~p ^ q) v (~p ^ r)
9 - distributiva
```

d)
```
~p -> ~q <=> q -> p
1 - condicional (contrapositiva)
2 - dupla negação
```

e)
```
~(~p v q) <=> (p ^ ~q)
~~p ^ ~q
p ^ q

2 lei de morgan e dupla negação
```

f)
```
p v q <=> ~(~p ^ ~ q)
~(~p ^ ~q) <=> ~~p v ~~q <=> p v q

1 lei de morgan e dupla negação
```

g)
```
~p -> p <=> p

~p -> p <=> ~~p v p <=> p v p

2 - dupla negacao
3 - Idem Potente
```
### 14
`Q: A aula termina mais cedo ou não há festa hoje`

a) Especifique a operação lógica envolvida em Q.
```
A operação lógica envolvida em Q é a OU
```

b) Escreva Q em linguagem simbólica.
```
p = A aula termina mais cedo
q = há festa hoje

p v ~q
```

c) Escreva pelo menos duas proposições logicamente equivalentes a Q, referenciando as equivalências utilizadas.
```
Q = p v ~q

Q <=> (~p -> ~q) <=> (~q v p)

Condicional e comutativa
```
d) Sabendo que a aula acabou mais cedo o que se pode afirmar sobre o valor lógico de Q

```
Q = p v ~q

O valor lógico de Q é verdade.
```

### 15
```
Se não estudarmos, não seremos bons profissionais

p = Se estudarmos
q = seremos bons profissionais

~p -> ~q
```


a) Determine a contrária da proposição dada.
```
p -> q
```

b) Determine a contrária da recíproca da contrapositiva da proposição gerada na alternativa a.
```
~q -> ~p
~p -> ~q
p -> q
```

c) Utilizando TVs verifique as equivalências lógicas existentes entre a contrapropositiva, a contraria a contrapositiva da proposição gerada na alternativa a.

| p  | q  | p -> q  | ~p -> ~q  | ~q -> ~p  | q -> p  |
| -  | -  | ------  | --------- | --------- | ------- |
| 1  | 1  | 1       |1          |1          |1        |
| 1  | 0  | 0       |1          |1          |0        |
| 0  | 1  | 1       |0          |0          |1        |
| 0  | 0  | 1       |1          |1          |1        |

```
reciproca <=> original
contrária <=> contrapositiva
```

