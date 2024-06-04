### 1

a)
```
Argumento: Todo o pensamento é um raciocínio, portanto todo o pensamento é um movimento, visto que todos os raciocínios são movimentos.

P1: Todo o pensamento é um raciocínio
P2: Todos os raciocínios são movimentos
C:  Todo pensamento é um movimento

P1
P2
--
C

Movimentos (
    Raciocionios (
        Pensamentos
    )
)

Argumento válido
```

b)
```
Se lógica é fácil, então Sócrates foi um grande matemático. Lógica não é fácil.
Portanto, Sócrates não foi um grande matemático.

p = Lógica é fácil
q = Sócrates foi um grande matemático

P1: Se lógica é fácil, então Sócrates foi um grande matemático
P2: Lógica não é fácil
C: Sócrates não foi um grande matemático

    F    V
P1: p -> q = V
P2: ~p     = V
---
C: ~q      = F
```

c)

```
Argumento: Todo o pensamento é um raciocínio, portanto todo o pensamento é um movimento, visto que todos os raciocínios são movimentos.

P1: Todo o pensamento é um raciocínio
P2: Todos os raciocínios são movimentos
C:  Todo pensamento é um movimento

P1
P2
--
C


p = todo o pensamento é um raciocinio
q = todos os raciocinios são movimentos
r = todo pensamento é um movimento

```
|p | q | r |
|- | - | - |
|1 | 1 | 1 |
|1 | 1 | 0 |
|1 | 0 | 1 |
|1 | 0 | 0 |
|0 | 1 | 1 |
|0 | 1 | 0 |
|0 | 0 | 1 |
|0 | 0 | 0 |

```
Se lógica é fácil, então Sócrates foi um grande matemático. Lógica não é fácil.
Portanto, Sócrates não foi um grande matemático.

p = Lógica é fácil
q = Sócrates foi um grande matemático

P1: Se lógica é fácil, então Sócrates foi um grande matemático
P2: Lógica não é fácil
C: Sócrates não foi um grande matemático
```

| p | q | p -> q | ~p |~q |
| - | - | -      |  - | - |
| 1 | 1 |     1  |  0 | 0 |
| 1 | 0 |     0  |  0 | 1 |
| 0 | 1 |     *1*  |  *1* | *0*|
| 0 | 0 |     1  |  1 | 1 |


### 2
a)
```

        V
P1: p v q = V

    V   F
P2: q v r = V
------
   F   F
C: p v r  = F

Argumento inválido, método da conclusão falsa
```

b)
```

    V
P1: a      = V
P2: a -> b = F
-------
C: b       = F

Argumento válido, método da conclusão falsa
```

c)
```

    F
P1:~a      = V
P2: a -> b = V
-------
C: ~b      = F

Argumento inválido, método da conclusão falsa

```

d)
```

    F
P1:~b      = V
P2: a -> b = F
-------
    V
C: ~a      = F

Argumento válido, método da conclusão falsa
```

e)
```


P1: b      = V
P2: a -> b = V
-------
C: a       = F

Argumento inválido, método da conclusão falsa
```

### 3

a)
```
Argumento válido

Método das premissas verdadeiras:
P1: p               = V
--
    V           V    = V
C: (p v q) ^ (p v r)

```

Método da TV:


| p(P1) | q  | r  | C    |
| -     | -  | -  | -    |
| *1*   | 1  | 1  | *1*  |
| *1*   | 1  | 0  | *1*  |
| *1*   | 0  | 1  | *1*  |
| *1*   | 0  | 0  | *1*  |
| 0     | 1  | 1  | 1    |
| 0     | 1  | 0  | 0    |
| 0     | 0  | 1  | 0    |
| 0     | 0  | 0  | 0    |

b)
```
Argumento válido

Método das premissas verdadeiras:
P1: p        = V
P2: (p -> q) = V
------
C: q v ~q    = V
```

Método da TV:

| p  | q  | P1   | C    |
| -  | -  | -    | -    |
| 1  | 1  | *1*  | *1*  |
| 1  | 0  | 0    | 1    |
| 0  | 1  | *1*  | *1*  |
| 0  | 0  | *1*  | *1*  |


c)
```
Argumento válido

Método do absurdo
    F   F
P1: p v p        = F
    F       F
P2: p -> (q ^ r) = V
----
C: r             = F


Método das premissas verdadeiras
    V   V
P1: p v p        = V
    V     V   V
P2: p -> (q ^ r) = V
----
C: r             = V

```

