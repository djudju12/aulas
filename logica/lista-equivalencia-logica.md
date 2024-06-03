# 1

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

# 2

Não é verdade que Pedro é pobre e Alberto é alto

~(p ^ q) <=> ~p v ~q

Não é verdade que Pedro é pobre ou Não é verdade que Alberto é alto

# 3

Não é verdade que Se Pedro é pobre então Alberto é alto

~(p -> q)

p ^ ~q

Pedro é pobre e não é verdade que Alberto é alto

# 4

Não é verdade que Pedro é pobre se Alberto é alto ???

# 5

Algum carro é veloz

Nenhum carro é veloz

# 6

Nem todo o livro é ilustrado

Nenhum livro é ilustrado

