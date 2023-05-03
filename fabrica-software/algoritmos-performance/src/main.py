# jonathan: quick, selection
from collections.abc import Callable
import csv
import datetime
import os
import numpy as np
from algoritmosPerformance import *

PARENT_FOLDER = r'.\vetores'
ALGORITMOS_TIME: list[Callable] = [quick_time, selection_time]
ALGORITMOS_COUNT: list[Callable] = [quick_count, selection_count]
PATH_RESULTADO = 'resultados.csv'
HEADER = ['Algoritmo', 'Cenario', 'Trocas', 'Comparacoes', 'Tempo']

def main() -> None:
    vetores = criar_vetores() 
    
    print('start: ', hora_agora())
    with open(PATH_RESULTADO, 'w', newline='') as f:
        writer = csv.writer(f)
        writer.writerow(HEADER)

        for algo_time, algo_count in zip(ALGORITMOS_TIME, ALGORITMOS_COUNT):
            for cenario in vetores.keys():
                vetor_time, vetor_count = make_2_copies(vetores[cenario])
                comparacoes, trocas = algo_count(vetor_count)
                tempo = algo_time(vetor_time)
                writer.writerow([algo_time.__name__, cenario, 
                                 str(trocas), str(comparacoes), 
                                 str(tempo)])

                print(f'{hora_agora()}: ', algo_time.__name__, cenario)

    print('End: ', hora_agora())

def make_2_copies(vetor: list) -> tuple[np.ndarray, np.ndarray]:
    vet = np.array(vetor)
    return vet.copy(), vet.copy() 

def hora_agora() -> str:
    return datetime.datetime.now().strftime('%H:%M:%S')


def criar_vetores() -> dict[str, list]:
    vetores = {}
    for vetor_path in os.listdir(PARENT_FOLDER):
        _, file_name = os.path.split(vetor_path)
        with open(os.path.join(PARENT_FOLDER, vetor_path), 'r') as f:
            vetor = np.array(list(map(int, f.read().split('\n'))))
            vetores[file_name[:-4]] = vetor
    return vetores


if __name__ == '__main__':
    main()