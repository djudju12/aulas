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

~(p -> q)

p ^ ~q

### 4

Não é verdade que Pedro é pobre sse Alberto é alto

~(p <-> q)
p + q


Pedro é pobre e não é verdade que Alberto é alto

### 5

Algum carro é veloz

Nenhum carro é veloz

### 6

Nem todo o livro é ilustrado

Nenhum livro é ilustrado

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
```

c) Paulo e Lucas são desenvolvedores

d) Paulo ou Lucas ou João são desenvolvedores.

### 10

