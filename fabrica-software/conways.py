# Any live cell with two or three live neighbours survives.
# Any dead cell with three live neighbours becomes a live cell.
# All other live cells die in the next generation. Similarly, all other dead cells stay dead.
import os
from random import choices
import time
LARGURA = 60 
ALTURA = 30

ZERO = " "
ONE = "\u25A0"
# ZERO = "#"
# ONE = "1"

generation = list[list[int]]

def rule_conways(vizinhos: str) -> bool:
    vizinhos_vivos = vizinhos[1:].count('1')
    if vizinhos_vivos == 3:
        return '1'
    elif vizinhos[0] == '1' and vizinhos_vivos == 2:
        return '1'
    else:
        return '0'

def make_dict() -> dict:
    rule_dict = {}
    for i in '10':    
        for n in range(2**8):
            bits = f'{i}{n:08b}'
            state_rule = rule_conways(bits)
            rule_dict[bits] = state_rule

    return rule_dict

def pegar_vizinhos(matrix: generation, pos_cel: tuple[int, int]) -> list[int]:
    x, y = pos_cel
    vizinhos = [str(matrix[x][y])]
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
            vizinhos.append(str(matrix[x][y]))
    while len(vizinhos) < 9:
        vizinhos.append('0')
    return "".join(vizinhos)
    
def weighted_int(densidade: int) -> int:
    return choices(['1', '0'], weights=(densidade, (100 - densidade)))[0]

def make_seed(densidade: int) -> generation:
    return [[weighted_int(densidade) for _ in range(LARGURA)] for _ in range(ALTURA)]

def next_gen(gen: generation, rule_dict: dict) -> generation:
    next_gen = []
    for x in range(ALTURA):
        linha = []
        for y in range(LARGURA):
            bits = pegar_vizinhos(gen, (x, y))
            linha.append(rule_dict[bits])
        next_gen.append(linha)
    return next_gen

def print_grid(grid: list[list[str]]) -> None:
    for x in range(ALTURA):
        print('\n', end='')
        for y in range(LARGURA):
            print(ONE if grid[x][y] == '1' else ZERO, end="")

def main():
    rule_dict = make_dict()
    matrix = make_seed(60)
    while True:
        print_grid(matrix)
        matrix = next_gen(matrix, rule_dict)
        time.sleep(0.3)
        os.system('cls')

if __name__ == '__main__':
    main()