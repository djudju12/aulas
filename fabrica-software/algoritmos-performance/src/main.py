# jonathan: quick, selection
from collections.abc import Callable
import csv
import datetime
import os
import numpy as np
from algoritmosPerformance import *

PATH = r'.\vetores'
CENARIOS = ['vetor1000-1',
            'vetor1000-2',
            'vetor1000-3',
            'vetor10000-1',
            'vetor10000-2',
            'vetor10000-3',
            'vetor50000-1',
            'vetor50000-2',
            'vetor50000-3',
            'vetor100000-1',
            'vetor100000-2',
            'vetor100000-3'
           ]
Function = Callable
ALGORITMOS_TIME: list[Function] = [quick_time, selection_time]
ALGORITMOS_COMP: list[Function] = [quick_count, selection_count]

def main() -> None:
    vetores: dict[str, int] = criar_vetores() 
    print('start: ', datetime.datetime.now().strftime('%H:%M:%S'))
    with open('resultados2.csv', 'w', newline='') as f:
        writer = csv.writer(f)
        writer.writerow(['Algoritmo', 'Cenario', 'Trocas', 'Comparacoes', 'Tempo'])
        for algo_time, algo_count in zip(ALGORITMOS_TIME, ALGORITMOS_COMP):
            for cenario in CENARIOS:
                comparacoes: int = 0
                trocas: int = 0 
            
                vetor_time: np.ndarray[int] = np.array(vetores[cenario]).copy()    
                vetor_count: np.ndarray[int] = np.array(vetores[cenario]).copy()    
                comparacoes, trocas = algo_count(vetor_count)
                tempo = algo_time(vetor_time)

                writer.writerow([algo_time.__name__, cenario, str(trocas), str(comparacoes), str(tempo)])
                print(f'{datetime.datetime.now().strftime("%H:%M:%S")}: ', algo_time.__name__, cenario)
    print('End: ', datetime.datetime.now().strftime('%H:%M:%S'))


def criar_vetores() -> dict:
    vetores = {}
    for vetor_path in os.listdir(PATH):
        _, tail = os.path.split(vetor_path)
        with open(PATH+'\\'+vetor_path, 'r') as f:
            vetor = np.array(list(map(int, f.read().split('\n'))))
            vetores[tail[:-4]] = vetor
    return vetores


if __name__ == '__main__':
    main()