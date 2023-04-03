# Trabalho de Fabrica de Software - Representacao de Cellular Automatons 2D "life-like"
# Jonathan Willian dos Santos - 03/04/2023 
# Fontes: 
# 1 - https://en.wikipedia.org/wiki/Cellular_automaton
# 2 - https://mathematica.stackexchange.com/questions/153388/how-to-calculate-cellularautomaton-rule-numbers-in-higher-dimensions
# Para o presente trabalho foi escolhido uma implementacao parcial
# Ou seja, soh estamos considerando casos onde os pesos das celulas vizinhas sao identicos ao do Conway's Game of Life
# A referencia 1 fala a respeito. Mas basicamente foi abstraido o K, WT e RSPEC "{n,{k,{wt 1,wt 2,...},rspec" e mantido apenas o N 

from random import choices
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap 
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2Tk
import tkinter as tk

LARGURA, ALTURA = 60, 60 
SELF_WEIGHT, CELL_WEIGHT = 1, 2 # Necessário para o cálculo das somas (será explicado melhor na função correspondente)
ZERO, ONE = " ", "\u25A0" # Espaco vazio e unicode para o caracter BLACK SQUARE. Constantes usadas na impressao do grid no terminal
POSSIBLE_STATES = [0, 1] 
DENSIDADE = 60 # Porcentagem de células vivas na primeira geracao 
SLEEP = 0.05


def main2():
    root = tk.Tk()
    fig = Figure(figsize=(5, 4), dpi=100)
    root.geometry('800x600')
    canvas = FigureCanvasTkAgg(fig, master=root)
    canvas.get_tk_widget().pack(side='top', fill='both', expand=1)

    grid = make_seed(DENSIDADE)
    rule_dict = rule(224)
    def draw_chart(grid):
        fig.clear()
        fig.add_subplot(111).plot(grid)
        canvas.draw_idle()
        grid = next_gen(grid, rule_dict)
    
    tk.Button(root, text="Draw", command=lambda: draw_chart(grid)).pack()

    root.mainloop()

def main():
    # conways => 224
    gen = make_seed(DENSIDADE)
    rule_dict = rule(224) 
    plot_grid2(gen, rule_dict)
    
# Aqui a definicao das regras são feitas.
def rule(rule: int) -> dict:
    # cria uma string de bits com o valor passado na regra. A string eh equivalente ao inteiro na base dois, porem a string foi eh invertida
    bit_str = make_bit_str(rule)
    # Acha os valores de somas dos pesos que resultarao em uma celula viva
    list_valid_sums = find_sums(bit_str)
    rule_dict = {}
    # 2**8 pois sao 8 vizinhos, ou seja, 8bits e mais um bit para a celula central
    for state in map(str, POSSIBLE_STATES):
        for n in range(2**8): 
            bit_number = f'{n:08b}' 
            # Conforme as referenciais, calcula as somas que resultam em uma celula viva
            current_sum = calc_sum(state, bit_number)
            # Mapeia a vizinhanca / resultado. A vizinha eh a celula central concatenada com o restante das celulas
            rule_dict[state+bit_number] = 1 if current_sum in list_valid_sums else 0
    return rule_dict

# 224 -> '000001110000000000', ou seja, representacao binaria invertida 
def make_bit_str(rule: int) -> str:
    return f'{rule:018b}'[::-1]

# ver referencia 
def find_sums(bit_str: str) -> list[int]:
    return [i for i, n in enumerate(bit_str) if n == '1']

# Retorna uma lista com as somas que resultam uma celula viva
def calc_sum(state: str, bit_number: str) -> int:
    sum = 0
    sum += SELF_WEIGHT*int(state) 
    total_live_cells = bit_number.count('1')
    sum += total_live_cells * CELL_WEIGHT
    return sum

# Constroi o grid inicial
def make_seed(densidade: int) -> list[list[int]]:
    return [[weighted_cel(densidade) for _ in range(LARGURA)] for _ in range(ALTURA)]

# retorna 1 ou 0 com pesos para 1 e 0
def weighted_cel(densidade: int) -> int:
    return choices(POSSIBLE_STATES, weights=(densidade, (100 - densidade)))[0]

# Funcao auxiliar para printar o grid no terminal 
def print_grid(grid: list[list[str]]) -> None:
    for x in range(ALTURA):
        print('\n', end='')
        for y in range(LARGURA):
            print(ONE if grid[x][y] == 1 else ZERO, end="")

# Para cada celula no grid busca seu proximo estado conforme o valor dos vizinhos
def next_gen(gen: list[list[int]], rule_dict: dict) -> list[list[int]]:
    next_gen = []
    for x in range(ALTURA):
        linha = []
        for y in range(LARGURA):
            bits = pegar_vizinhos(gen, (x, y))
            linha.append(rule_dict[bits])
        next_gen.append(linha)
    return next_gen

# Pega os vizinhos da celula re torna como uma string para ser usada como key no dicionario
def pegar_vizinhos(gen: list[list[int]], pos_cel: tuple[int, int]) -> list[str]:
    x, y = pos_cel
    vizinhos = [str(gen[x][y])]
    permutacoes = ((x - 1, y + 1),
                   (x - 1, y),
                   (x - 1, y - 1),
                   (x, y + 1),
                   (x, y - 1),
                   (x + 1, y + 1),
                   (x + 1, y),
                   (x + 1, y - 1))     
    for x, y in permutacoes:
        if x < ALTURA and x >= 0 and y < LARGURA and y >= 0:
            vizinhos.append(str(gen[x][y]))
        else:
            vizinhos.append('0')
    return "".join(vizinhos)

def plot_grid2(grid: list[list[int]], rule_dict: dict):
    plt.ion()
    # Fullscreen. Não tenho a solucao para fechar a janela ainda
    # manager = plt.get_current_fig_manager()
    # manager.full_screen_toggle()
    while True:
        plt.matshow(grid, fignum=0, cmap=ListedColormap(['white', 'black']))
        plt.draw()
        grid = next_gen(grid, rule_dict)
        if plt.waitforbuttonpress(SLEEP):
            plt.close()
            return
        plt.clf()

if __name__ == '__main__':
    main()