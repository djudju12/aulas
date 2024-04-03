1) Encontre o valor lógico das proposições abaixo
    * 3+4=7 ou 2+2=4

          V ^ V == V

    * 8<4 e 6>3

          F v V == V

    * 6<0 ou 3=4

          F v F == F

    * 3>5 e 8>6

          F && V == F

    * 7>8 → ~ (5<4)

          F → ~F
          F → V == V

    * Se 2 é par então 3 é impar

          par?(2) → impar?(3)
          V → V == V

    * Se 5 é inteiro então 3 é menor que 5

          N?(5) → (3 < 5)
          V → V == V

    * Se 8 é impar então 7 é menor que 3

          impar?(8) → (7 < 3)
          F → F == V

    * 3>5 e 8>6

          F ^ V == F

    * ~ (5>17) → 9<4

          ~(F) → F
          V → F == F

    * ~ (1+1=2 ↔ 3+4=5)

          ~(F ↔ F)
          ~V == F

    * ~ (2+2 ≠ 4 ^ 3+5=8)

          ~(F ^ V)
          ~F == V

    * 43 ≠ 64 ↔ (3+3 =7 ↔11+2=12)

          V ↔ (F ↔ F)
          V ↔ V == V

    * 23 ≠ 8 v 43 ≠ 42

          V v V == V

    * 34=81 ↔ ~(2+1 =3 ^ 5*0=0)

          F ↔ ~(V ^ V)
          F ↔ ~V
          F ↔ F == V

2) Considere a afirmação P: (a v b) onde a e b por sua vez são as seguintes afirmações: a= Carlos é dentista e b = Se Enio é economista então Juca é arquiteto. Sabe-se que a afirmação P é falsa logo:

P: (a v (c <-> d)) == F
a: Carlos é dentista
c: Enio é economista
d: Juca é Arquiteto

~(a v (c <-> d))


* Carlos não é dentista, Ênio não é economista e Juca não é arquiteto.

      (F v (F <-> F))
      (F v V)
      V != P

* Carlos não é dentista, Ênio é economista, Juca não é arquiteto.

      (F v (V <-> F))
      (F v F)
      F == P :: Resposta Certa

c) Carlos é dentista, Ênio não é economista e Juca não é arquiteto

      (V v (F <-> F))
      (V v V)
      V != P

d) Carlos é dentista, Ênio é economista e Juca não é arquiteto

      (V v (V <-> F))
      (V v F)
      V != P

3) A afirmação “Alda é alta” ou “Bino não é baixo” ou “Ciro é calvo” é falsa. Segue-se, pois, que é verdade que:

a = Alda é alta
b = Bino não é baixo
c = Ciro é calvo

(a v ~b v c) == F
ou seja, todas as afirmações são falsas

a = Alda não é alta
b = Bino é baixo
c = Ciro não é calvo


a) Se Bino é baixo, Alda é alta e Se bino não é baixo, Ciro não é calvo.

      ((V -> F) ^ (F -> V))
      (F ^ V)
      F

b) Se Alda é alta, Bino é baixo, e Se Bino é baixo, Ciro é calvo.

      ((F -> V) ^ (V -> F))
      (V ^ F)
      F

c) Se Alda é alta, Bino é baixo e Se Bino não é baixo, Ciro não é calvo.

      ((F -> V) ^ (F -> V))
      (V ^ V)
      V :: Resposta Certa


d) Se Bino não é baixo, Alda é alta e Se Bino é baixo, Ciro é calvo.

      ((F -> F) ^ (V -> F))
      (V ^ F)
      F

e) Se Alda não é alta, Bino não é baixo, e Se Ciro é calvo, Bino não é baixo

      ((V -> F) ^ (F -> F))
      (F ^ V)
      F














Para cada um dos arranjos abaixo determine se são FBFs, aponte o erro e
a regra violada:
1. p v ~q -> FBF
2. r ~v t -> ~ junto do conectivo
3. p -> FBF
4. p ^ (r ~s) -> ~ entre proposiçoes
5. p → ~q -> FBF
6. p → ~ (p ^ → q) -> conectivo do lado de conectivo
7. p (→ q → p) -> conectivo dentro dos parentes
8. (p v q → q) -> ambigua
9.  [(pq)] v ~r -> duas preoposicoes sem conectivos
10. ~p ( v ~r ) ^ ~s ) -> parenteses errado
11. p v ^q → -> dois conectivos seguidos
12. p v q ~ → -> ~ sem proposicao
13. pq -> proposicoes sem conectivo
14. p ^ (q v~r) -> FBF
15. p ~ q -> negacao entre duas proposicoes


1. Construa a tabela verdade das proposições abaixo:
a) (p ^ q) → ~p

|p   |q   |(p ^ q) → ~p   |
|:--:|:--:|:-------------:|
| 1  | 1  |    0          |
| 1  | 0  |    1          |
| 0  | 1  |    1          |
| 0  | 0  |    1          |

b) (p → q) v p

|p     |q     |(p → q) v p      |
|:---: |:---: |:--------------: |
| 1    | 1    | 1 v 1 -> 1      |
| 1    | 0    | f v 1 -> 1      |
| 0    | 1    | 1 v 0 -> 1      |
| 0    | 0    | 1 v 0 -> 1      |

c) (p → ~q) ^ q

|p     |q     |(p → ~q) ^ q     |
|:---: |:---: |:--------------: |
| 1    | 1    |(1 → 0)^1 -> 0   |
| 1    | 0    |(1 → 1)^0 -> 0   |
| 0    | 1    |(0 → 0)^1 -> 1   |
| 0    | 0    |(0 → 1)^0 -> 0   |

d) (q → p) → (p v q)

|p     |q     |(q → p) → (p v q) |
|:---: |:---: |:----------------:|
| 1    | 1    | 1 → 1 ->   1     |
| 1    | 0    | 1 → 1 ->   1     |
| 0    | 1    | 0 → 1 ->   1     |
| 0    | 0    | 1 → 0 ->   0     |


e) ~q → (p v q)

|p     |q     |~q → (p v q)|
|:---: |:---: |:----------:|
| 1    | 1    | 0 → 1 -> 1 |
| 1    | 0    | 1 → 1 -> 1 |
| 0    | 1    | 0 → 1 -> 1 |
| 0    | 0    | 1 → 0 -> 0 |


f) (p v q) v (p ↔ q)

|p     |q     |(p v q) v (p ↔ q) |
|:---: |:---: |:----------------:|
| 1    | 1    | 1 v 1 -> 1       |
| 1    | 0    | 1 v 0 -> 1       |
| 0    | 1    | 1 v 0 -> 1       |
| 0    | 0    | 0 v 1 -> 1       |


g) [(p → q) v (p ^ q)] ^ (p v q)

|p     |q     |[(p → q) v (p ^ q)] ^ (p v q)|
|:---: |:---: |:--------------------------: |
| 1    | 1    |1 ^ 1 -> 1                   |
| 1    | 0    |0 ^ 1 -> 0                   |
| 0    | 1    |1 ^ 1 -> 1                   |
| 0    | 0    |1 ^ 0 -> 0                   |


h) [(q → p) → (p ↔ q)] → (p v q)

|p     |q     |[(q → p) → (p ↔ q)] → (p v q)|
|:---: |:---: |:---------------------------:|
| 1    | 1    |1 → 1 -> 1                   |
| 1    | 0    |0 → 1 -> 1                   |
| 0    | 1    |1 → 1 -> 1                   |
| 0    | 0    |1 → 0 -> 0                   |

