### 1 Refencie a regra de inferência utilizada na conclusão dos argumentos abaixo

a) `p → q, q → r C: p → r               1,2 (SH)`

b) `t → (s v t), (s v t) → p C: t → p   1,2 (SH)`

c) `(r → s) v (p → q), ~ (r → s) C: p → q 1,2 (SD)`

d)
```
(p → r) = G    (q → r) = H
(G → s) ^ (H → t), G v H C: s v t 1,2 (DC)
```

e) `(s v p) ^ m C: s v p 1 (SIMP)`

f) `~p → ~q, ~q → ~r C: ~p →~r 1,2 (SH)`

g) `(~p → q) ^ (~r → s), ~p v ~r C: q v s 1,2 (DC)`

h) `(p ^ q) → r, r → ~p C: (p ^ q) → ~p 1,2 (SH)`

i) `(p ^ q) v (r→ s), ~(p ^ q) C: r → s 1,2 (SD)`

j)
```
G = (p ^ r)
H = (p v r)
(G → ~s) ^ (H → ~t), G v H C: ~s v ~t 1,2 (SIMP E DC)
```

### 2 Apresente conclusão dos argumentos, referenciando as regras de inferência utilizadas

a)
```
P1: p v q
C: p v q
```

### 3 demonstre a validade dos argumentos, utilizando regras de inferencia

a)
```
P1: (p ^ q) → (r ^ s)
P2: p
P3: q
P4: r ^ s (1, 2, 3 MP)
P5: s (4 SIMP)
C: s
```

b)
```
P1: p ^ (q v r)
P2: (q v r) → ~s
P3: s v t
P4: q v r (1 SIMP)
P5: ~s (2 MP)
P6: t (5, 3 SD)
C: t
```

c)
```
P1: (p → q)
P2: (r → t)
P4: ~q
P5: (p v r) ^ (q v t)
P6: q v t (5 SIMP)
P7: t (4, 6 SD)
C: t
```

### 4 Demonstre a validade dos argumentos utilizando regras de Inferência

a)
```
P1: (t ^ ~q) → ~s
P2: t ^ (~q ^ r)
P3: (~q ^ r) (2 SIMP)
P4: ~s (3, 1 MP)
C: ~s

```

b)
```
P1: s
P2: ~(s ^ t)
P3: ~s v ~t
P4: ~t (SD)
C: ~t
```

c)
```
P1: p → q
P2: r
P3: ~p  → ~r
P4: p (3 MT)
P5: q (1 4 MP)

C: q
```

d)
```
P1: ~c
P2: a v (c ^ d)
P3: a     ^- F
C: a
```

e)
```
P1: s → ~q
P2: p → q
P3: s
P4: ~q
P5: ~p
C: ~p
```