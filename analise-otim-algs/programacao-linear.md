## Programação Linear

### Objetivo:

Obtenção da melhor solução - solução "ótima" - para problemas cujos modelos associados são lineares. 

**Problemas de alocação de recursos**.

    Atribuição e distribuição de recursos entre as diversas tarefas ou atividades que devem ser realizadas 

Cracterizam-se pela existência de:

* Objetivos que podem ser expressoes pelas variáveis de decisão do problema
* Restrições à aplicação dos recursos (quantidade e forma de aplicação)

Maximação ou Miniização da **Função Objetiva** -> **Solução Ótima**

Passos para modelagem dos problemas:
1. identificar as variáveis desconhecidas a serem determinadas - **variáveis de decisão**;
2. listar as restrições do problema em função das váriaveis de decisão;
3. identificar o objetivo ou critério de otimização do problema -  função linear com variáveis de decisão.

### Exemplo 1:

Uma empresa fabrica cadeiras e mesas. Cada cadeira necessita, para sua produção, de 5 tábuas de madeira e cada mesa, 20. Ao todo, a empresa dispõe de 400 tábuas. 

A produção de cada cadeira consome 10 horas de trabalho cada mesa, 15 horas. Há 450 horas disponíveis. 

O lucro por cadeira é de R$ 180,00 e por mesa é de R$ 320,00.

Qual é o número de cadeiras e de mesas que torna o lucro máximo? E qual é o seu valor?

método gráfico

1. criar um gráfico com x1 e x2 nos eixos
2. Traçar as retas do grafico calculando qnt max de tabuas e horas pra x1 == 0 e x2 == 0 
3. Verificar as coordenadas onde as linhas se cruzam
4. Checar qual é a equação que da mais lucro

x1 = 0 

5*0 + 20x2 = 400

x2 = 400 / 20 = 20

x2 = 0

5x1 + 20*0 = 400

x1 = 400 / 5 = 80

x1 = 0 

10*0 + 15x2 = 450

x2 = 30 

x2 = 0 

x1 = 45 

a gente tem os seguintes pontos
reta das tabuas (80, 0), (0, 20)
reta das horas (45, 0), (0, 30)

para calcular o ponto que passa pelas duas retas

5x1 + 20x2 = 400

10x1 + 15x2 = 450

x2 = 14

x1 = 24