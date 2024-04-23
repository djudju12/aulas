1) Com suas palavras, responda as seguintes questões:

a) Quais são os princípios básicos da lógica? Explique-os.

A lógica possuí três princípos básicos, sendo eles:

### Identidade

Para um preposição `p`, se `p` for verdadeira então ela será verdadeira.
Se for falsa, então, `p` sera falsa.

### Não-contradição

Uma preposição `p` não pode ser verdadeira e falsa ao mesmo tempo

### Terceiro Excluído

Os únicos valores possivéis para a proposição `p` é verdadeiro ou falso.

b) Apresente no mínimo duas situações cotidianas em que a lógica pode ser aplicada.

1. Ao desenvolver qualquer tipo de software;
2.

c) O que são FBFs e quais são as principais regras que devem ser aplicadas sobre
proposições para que as mesmas sejam consideradas FBFs?

FBFs é a sigla para "fórmulas bem formadas", que consistem em proposições complexas escritas
em suas notações simbólicas. Tais proposições devem seguir uma enumeração de regras para
serem consideradas válidas e, portanto, FBFs, sendo elas:

R1: conectivos lógicos (^, v, ->, <->) devem ficar entre proposições

R2: A negação deve ficar na frente de uma proposição

R3: A negação não deve ficar sozinha entre duas proposições

R4: Parenteses para evitar ambiguidades


d) Diferencie proposições tautológicas, contraditórias e contigentes, explicando suas
particularidades. Exemplifique-as.

A tautologia pode ser definida por uma proposição P que possui apenas valores de verdade em
sua coluna resultado, exemplo `(q v p) v ~q`;

A contradição é o inverso da tautologia, onde o resultado da proposição P será sempre falso.
Exemplo `~p ^ p`;

A contigência se dá quando os valores de P assumem tanto valores falsos quanto verdadeiros,
como em `p v q`;

e) Discorra sobre implicação lógica e o que diferencia das proposições tautológicas,
contraditóris e contigentes.

A implicação lógica, denotada por `p => P`, indica que a proposição p possui, pelo menos uma
vez, um valor de verdade para quando P for verdade também.

7) Cosiderando as proposições abaixo:

7.1) Se Beto briga com Glória, então Glória vai ao cinema. Se Glória vai ao cinema, então
Carla fica em casa. Se Carla fica em casa, então Raul briga com Carla. Ora, Raul briga com Carla.

7.2) Se Ana não é advogada, então Sandra é secretária. Se Ana é advogada, então Paula não é
professora. Ora, Paula é professora.

Determinar:

a) A representação simbólica das proposições.
```
p = Beto briga com Glória
q = Glória vai ao cinema
k = Carla fica em casa
j = Raul briga com Carla

p -> q = Se Beto briga com Glória, então Glória vai ao cinema
q -> k = Se Glória vai ao cinema, então Carla fica em casa
k -> j = Se Carla fica em casa, então Raul briga com Carla
```
---
```
p = Ana é advogada
q = Sandra é secretária
k = Paula é professora

~p -> q = Se Ana não é advogada, então Sandra é secretária
p -> ~k = Se Ana é advogada, então Paula não é professora
```

b) A TV
```
|p | q | p -> q |
|--|---|--------|
|1 | 1 |  1     |
|1 | 0 |  0     |
|0 | 1 |  1     |
|0 | 0 |  1     |

|q | k | q -> k |
|--|---|--------|
|1 | 1 |  1     |
|1 | 0 |  0     |
|0 | 1 |  1     |
|0 | 0 |  1     |

|k | j | k -> j |
|--|---|--------|
|1 | 1 |  1     |
|1 | 0 |  0     |
|0 | 1 |  1     |
|0 | 0 |  1     |

```
---
```
|p | q | ~p -> q|
|--|---|--------|
|1 | 1 |  1     |
|1 | 0 |  1     |
|0 | 1 |  1     |
|0 | 0 |  0     |

|p | k | p -> ~k|
|--|---|--------|
|1 | 1 |  0     |
|1 | 0 |  1     |
|0 | 1 |  1     |
|0 | 0 |  1     |
```

c) A árvore semântica das proposições, determiando se são tautologias, contradições ou contigências

d) Verifique a existência de equivalência lógica entre as proposições

e) Verificiar se as proposições obitidas implicam entre si, demonstrando as relações de implicação
na TV

f) Comprove as relações de implicação lógica, utilizando-se do método indireto

g) A partir do método indireto e do uso da TV determine as verdades estabelecidas a partir do valor
lógico das proposições

