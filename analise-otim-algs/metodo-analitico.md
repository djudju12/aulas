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

| x1 | x2   | x3  | x4 | x5 | rs| 
| -  |  -   |  -  |  - | -  | - | 
| -3 |  0   |  0  | 5  |  0 | 30 |
| 0  |  0   | _1_ |  0 |  0 | 4 |
| 0  | _1_ |  0  | 1  |  0 | 6 |
| 3  | 0    |  0  | -2 | _1_ | 6 |

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



