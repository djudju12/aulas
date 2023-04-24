# Para análise comparativa serão utilizados os seguintes indicadores:
# Comparações;Trocas;Tempos 
# As massas de dados serão de 1000, 10000, 50000, 100000
import json
import numpy as np
from algortimosItem4 import *
from timeit import timeit

MIN_VALUE = 0
MAX_VALUE = 100
ALGORITMOS = {
    'time': [insertion_sort_time, bubble_sort_time], 
    'comparasoes': [insertion_sort_comparasoes, bubble_sort_comparacoes]
} 
NUMBER_OF_TESTS = 100

def make_vector(size: int) -> np.ndarray:
    return np.random.randint(MIN_VALUE, MAX_VALUE, size)

def main():
    vectors = {
        'PEQUENO': make_vector(10), 
        'GRANDE' :make_vector(50), 
        'SUPER-GRANDE': make_vector(100)
        }
    
    results = {}

    results['time'] = {}
    for algoritmo in ALGORITMOS['time']:
        results['time'][algoritmo.__name__] = {}
        for vector in vectors.keys():
            copied_vector = vectors[vector].copy()
            t = timeit(lambda: algoritmo(copied_vector), number=NUMBER_OF_TESTS)
            # results['time'][algoritmo.__name__][vector] = 
            results['time'][algoritmo.__name__][vector] = t 

    results['comparacoes'] = {}
    results['trocas'] = {}
    for algoritmo in ALGORITMOS['comparasoes']:
        results['comparacoes'][algoritmo.__name__] = {}
        results['trocas'][algoritmo.__name__] = {}
        for vector in vectors.keys():
            comparacoes, trocas = 0, 0
            for _ in range(NUMBER_OF_TESTS):
                copied_vector = vectors[vector].copy()
                c, t = algoritmo(copied_vector)
                comparacoes += c
                trocas += t
            results['comparacoes'][algoritmo.__name__][vector] = comparacoes
            results['trocas'][algoritmo.__name__][vector] = trocas

    results = {'results': results}
    json_str = json.dumps(results)
    print(json_str)

if __name__ == '__main__':
    main()
