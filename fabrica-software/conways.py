# Any live cell with two or three live neighbours survives.
# Any dead cell with three live neighbours becomes a live cell.
# All other live cells die in the next generation. Similarly, all other dead cells stay dead.
from random import choices
ALTURA = 8
LARGURA = 8 

# ZERO = " "
# ONE = "\u25A0"
ZERO = "#"
ONE = "1"

generation = list[list[int]]

def rule_conways(vizinhos: str) -> bool:
    vizinhos_vivos = vizinhos.count('1')
    if vizinhos_vivos == 3:
        return lambda x: '1' if True or x else '0'
    elif vizinhos_vivos == 2:
        return lambda x: '1' if True and x else '0'
    else:
        return lambda x: '0'

def make_dict() -> dict:
    rule_dict = {}
    for n in range(2**8):
        bits = f'{n:08b}'
        state_rule = rule_conways(bits)
        rule_dict[bits] = state_rule
    return rule_dict


def pegar_vizinhos(matrix: generation, pos_cel: tuple[int, int]) -> list[int]:
    vizinhos = []
    permutacoes = ((pos_cel[0] - 1, pos_cel[1] + 1),
                   (pos_cel[0] - 1, pos_cel[1]),
                   (pos_cel[0] - 1, pos_cel[1] - 1),
                   (pos_cel[0], pos_cel[1] + 1),
                   (pos_cel[0], pos_cel[1] - 1),
                   (pos_cel[0] + 1, pos_cel[1] + 1),
                   (pos_cel[0] + 1, pos_cel[1]),
                   (pos_cel[0] + 1, pos_cel[1] - 1))     
    for x, y in permutacoes:
        if x < LARGURA and x >= 0 and y < ALTURA and y >= 0:
            vizinhos.append(str(matrix[x][y]))

    while len(vizinhos) < 8:
        vizinhos.append('0')
    return "".join(vizinhos)
    
def weighted_int(densidade: int) -> int:
    return choices([1, 0], weights=(densidade, (100 - densidade)))[0]

def make_seed(densidade: int) -> generation:
    return [[weighted_int(densidade) for _ in range(LARGURA)] for _ in range(ALTURA)]

def next_gen(gen: generation, rule_dict: dict) -> generation:
    return [[rule_dict[pegar_vizinhos(gen, (x, y))](gen[x][y]) for x in range(LARGURA)] for y in range(ALTURA)]

def print_grid(grid: list[list[str]]) -> None:
    for x in range(LARGURA):
        print('\n', end='')
        for y in range(ALTURA):
            print(ONE if grid[x][y] == '1' else ZERO, end="")

def main():
    rule_dict = make_dict()
    matrix = [[0, 1, 0, 0, 0, 0, 1, 0],
              [1, 1, 0, 0, 0, 0, 0, 1],
              [0, 0, 1, 1, 1, 0, 0, 0],
              [0, 0, 1, 0, 1, 0, 0, 0],
              [0, 0, 1, 1, 1, 0, 0, 0],
              [0, 0, 0, 0, 0, 0, 0, 0],
              [0, 0, 0, 0, 0, 0, 1, 0],
              [0, 0, 0, 0, 0, 0, 1, 0]]
    
    print(matrix)
    print('\n')
    next_g = next_gen(matrix, rule_dict)
    print_grid(next_g)
    print('\n')
    print_grid(next_gen(next_g, rule_dict))

if __name__ == '__main__':
    main()