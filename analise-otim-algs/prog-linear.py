#!/usr/bin/python3

import matplotlib.pyplot as plt

# Uma empresa fabrica cadeiras e mesas. Cada cadeira necessita, para sua produção, de 5 tábuas de madeira e cada mesa, 20. Ao todo, a empresa dispõe de 400 tábuas. 
# A produção de cada cadeira consome 10 horas de trabalho cada mesa, 15 horas. Há 450 horas disponíveis. 
# O lucro por cadeira é de R$ 180,00 e por mesa é de R$ 320,00.
# Qual é o número de cadeiras e de mesas que torna o lucro máximo? E qual é o seu valor?

# 1. Definir as variáveis
x1: int = 0 # qnt de cadeiras
x2: int = 0 # qnt de mesas 

# 2. Definir as restrições

# tabuas
# 5*x1 + 20*x2 <= 400

# horas
# 10*x1 + 15*x2 <= 450

# 3. Definir a função objetivo
# L = 180x1 + 320x2 

# método gráfico

# 1. criar um gráfico com x1 e x2 nos eixos
x1_tabuas = lambda x2: (400 - 20*x2) / 5
x2_tabuas = lambda x1: (400 - 5*x1)  / 20
x1_horas = lambda x2:  (450 - 15*x2) / 10
x2_horas = lambda x1:  (450 - 10*x1) / 15


# 2. Traçar as retas do grafico calculando qnt max de tabuas e horas pra x1 == 0 e x2 == 0 
x1_t, x2_t = x1_tabuas(0), x2_tabuas(0)
x1_h, x2_h = x1_horas(0), x2_horas(0)

# Plot the line
plt.plot(x, y)

# Show the plot
plt.show()

# 3. Verificar as coordenadas onde as linhas se cruzam
# 4. Checar qual é a equação que da mais lucro