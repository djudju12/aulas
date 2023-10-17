## Metodo Analitico

max z = 3x1 + 5x2

sujeito a : 

| x1 <= 4

| x2 <= 6

| 3x1 + 2x2 <= 18

x1 + x3 = 4

x2 + x4 = 6

3x1 + 2x2 + x5 = 18

z - 3x1 - 5x2 = 0

| x1 | x2  | x3  |  x4 | x5  | rs | 
| -  | -   |  -  |   - |  -  |  - | 
| -3 | -5  | 0   |   0 | 0   | 0  | 
| 1  |  0  | _1_ | 0   | 0   | 4  | 
|  0 | *1* | 0   | _1_ | 0   | 6  |  -> LINHA e *ELEMENTO* PIVO
|  3 |  2  | 0   |  0  | _1_ | 18 |

matrix identidade em italico = variaveis básicas 

x3, x4, x5

variaveis básicas serão igualdas ao rs (lado direito)

x3 = 4

x4 = 6

x5 = 18

o restante das variaveis serão não-básicas e == 0

x1 = x2 = 0

| x1 | x2  | x3  | x4 | x5  | rs | 
| -  |  -  |  -  |  - | -   | -  | 
| -3 |  0  |  0  | 5  |  0  | 30 |
| 0  |  0  | _1_ |  0 |  0  | 4  |
| 0  | _1_ |  0  | 1  |  0  | 6  |
| 3  | 0   |  0  | -2 | _1_ | 6  |

X3, X2, X5

X3 = 4

X2 = 6

x5 = 6 

| x1 | x2 | x3 | x4   | x5    | rs | 
| -  | -  | -  |  -   | -     | -  | 
| 0  | 0  |  0 | 3    |  1    | 36 |
| 0  | 0  |  1 | 2/3  | -1/3  |  2 |
| 0  | 1  |  0 |  1   |  0    |  6 |
| 1  | 0  |  0 | -2/3 | 1/3   |  6 |

x3 = 2

x2 = 6

x1 = 2 

resposta x1 = 2, x2 = 6

max z = 5x1 + 5x2 

sujeito a : 

| 6x1 + 4x2 <= 24

|  x1 + 2x2 <= 6

| -x1 + x2  <= 1 

|       x2  <= 2 

|  x1 x2 >= 0

6x1 + 4x2 = 24 
{
 
  x1 = 4

  x2 = 6

}

x1 + 2x2 = 6
{

  x1 = 6

  x2 = 3

}

-x1 + x2 = 1 
{

  x1 = -1

  x2 = 1

}

x2 = 2 

(faz o gráfico pipipi pópópó) 

z = 5x1 + 4x2 

z = 10 

5x1 + 4x2 = 10

para x1 = 0 x2 = 2.5 

para x1 = 2 x2 = 0

a direção que a reta do Z sobe mostra para nós qual será o ponto ótimo
basta pegar enta o as duas do possivel ponto ótimo e testar
se ficar dúvida basta fazer dos outros também 


6x1 + 4x2 = 24

x1 + 2x2 = 6

resolvendo...

x2 = 1.5, x1 = 3

z = 21 :) 

### metodo analitico 

z - 5x1 - 4x2 = 0

6x1 + 4x2 + x3 = 24 

x1 + 2x2 + x4 = 6 

-x1 + x2 + x5 = 1 

x2 + x6 = 2 

| x1 | x2 | x3 | x4 | x5 | x6 | rs | 
| -  |  - |  - |  - | -  | -  |  - | 
| -5 | -4 | 0  |  0 |  0 | 0  | 0  | 
|*6* |  4 |_1_ |  0 |  0 | 0  | 24 | *24/6=4 -> linha pivot*
| 1  |  2 | 0  | _1_|  0 | 0  | 6  | *6/1=6*
| -1 | 1  | 0  |  0 | _1_| 0  | 1  | *(-1 não divide)* 
|  0 | 1  | 0  |  0 |  0 |_1_ | 2  | *(0 não divide)*

variaveis basicas:

x3 = 24, x4 = 6, x5 = 1, x6 = 2

variaveis nbasicas:

x1 = 0, x2 = 0

coluna pivot (menor valor da 1ª linhas) = 0 

linha pivot = 1

elemento pivot = 1x0

pegar o rs / coeficientes *

| x1 | x2 | x3 | x4 | x5 | x6 | rs | 
| -  |  - |  - |  - | -  | -  |  - | 
| 0  |-4/6|5/6 |  0 | 0  | 0  | 20 | 
| 1  |4/6 |1/6 |  0 | 0  | 0  | 4  | 4/(4/6) =  0.667
| 0  |4/3 |-1/6|  1 | 0  | 0  | 2  | 2/(4/3) = 
| 0  |5/3 |1/6 |  0 | 1  | 0  | 5  | 5/(5/3)
| 0  |*1* | 0  | 0  | 0  | 1  | 2  | 1/2     = 0.5 pivot 

----- essa parte acontece apos os calculos ----- 

variaveis basicas x1 = 4, x4 = 2, x5 = 5, x6 = 2 

variaveis nbasicas x2 = 0, x3 = 0

coluna pivot = 1 

linha pivot =  4 

elemento = 4x1 = 1 

------------------------------------------------

linha 0 calculo

1  4/6 1/6   0  0   0   4  

* *5*

=   5   20/6  5/6   0   0    0    20 -> linha 0 * *-seu_pivot(-5)*

+  -5    -4    0    0   0    0     0 -> linha 0

=   0   -4/6  5/6   0   0    0    20 -> linha 0 calculada

linha 1 foi calculada direto no passo anterior dividindo todos os seus elementos pelo pivot

linha 2 calculo 
     
  1  4/6 1/6   0  0   0   4

* -1

= -1  -4/6 -1/6  0  0   0 -4

+ 1   2     0    1  0   0  6

=  0  4/3   -1/6  1 0   0  2 

linha 3 calculo 

  1  4/6 1/6   0  0   0   4

* 1

= 1  4/6 1/6  0  0   0  4 

+ -1  1   0   0  1   0  1

= 0   5/3 1/6 0  1   0  5

linha 4 calculo pivot = 0 entao a linha nao muda 

| x1 | x2 | x3 | x4 | x5 | x6 | rs |
| -  |  - |  - |  - | -  | -  |  - | 
| 0  | 0  |5/6 |0   | 0  |4/6 |64/3|
| 1  | 0  |1/6 |0   | 0  |-4/6|-8/3|
|
| 0  | 1  | 0  | 0  | 0  | 1  | 2  |

calculo linha 0: 

  0   1   0   0   0   1   2  

* 4/6

= 0  4/6  0   0   0  4/6  4/3

+ 0 -4/6 5/6  0   0  0    20

= 0  0   5/6  0   0  4/6  64/3

calculo linha 1: 

  0   1   0   0   0   1   2  

* -4/6 

= 0  -4/6 0  0  0  -4/6  -4/3

+ 1  4/6 1/6 0  0    0    4

= 1  0   1/6 0  0   -4/6  -8/3 


