# Any live cell with two or three live neighbours survives.
# Any dead cell with three live neighbours becomes a live cell.
# All other live cells die in the next generation. Similarly, all other dead cells stay dead.
ALTURA = 8
LARGURA = 8 

def rule_conways(vizinhos: str) -> bool:
    vizinhos_vivos = vizinhos.count('1')
    if vizinhos_vivos == 3:
        return lambda x: True or x
    if vizinhos_vivos == 2:
        return lambda x: True and x
    return False

def make_dict() -> dict:
    rule_dict = {}
    for n in range(2**8):
        bits = f'{n:08b}'
        state_rule = rule_conways(bits)
        rule_dict[bits] = state_rule
    return rule_dict


def pegar_vizinhos(matrix: list[list[int]], pos_cel: tuple[int, int]) -> list[int]:
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
            vizinhos.append(matrix[x][y])

    return vizinhos
    

def main():

    rule_dict = make_dict()
    matrix = [[0, 1, 0, 0, 0, 0, 0, 0],
              [1, 1, 0, 0, 0, 0, 0, 0],
              [0, 0, 1, 1, 1, 0, 0, 0],
              [0, 0, 1, 0, 1, 0, 0, 0],
              [0, 0, 1, 1, 1, 0, 0, 0],
              [0, 0, 0, 0, 0, 0, 0, 0],
              [0, 0, 0, 0, 0, 0, 0, 0],
              [0, 0, 0, 0, 0, 0, 0, 0]]
    

    print(pegar_vizinhos(matrix, (7, 7)))

if __name__ == '__main__':
    main()