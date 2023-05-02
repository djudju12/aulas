# jonathan: quick, selection
import json
import os
import numpy as np
from algoritmos import *

PATH = r'.\vetores'
NOME_VETORES = 'pequeno', 'medio', 'grande', 'supergrande'
NOME_CENARIOS = 'C1', 'C2', 'C3'

def main():
    vetores = random_vetor()
    
    resultados = {}
    # tamanho do vetor 1, 2, 3, 4 
    for vetor in NOME_VETORES:
        cenarios = {}
        # cenario 1, 2, 3
        for cenario in NOME_CENARIOS:
            v = vetores.copy()
            t = selection_sort(v)
            cenarios[cenario] = {}
            cenarios[cenario].update({'trocas': t})
            cenarios[cenario].update({'comparacoes': t})
            cenarios[cenario].update({'tempo': t})
        resultados[vetor] = cenarios
    
    algoritmos = {'selection_sort': resultados}
    print(json.dumps(algoritmos))

    #  algoritmos :
    #       'insertion_sort':
    #           'pequeno':
    #               'C1':
    #                  'trocas':   
    #                  'comparacoes':   
    #                  'tempo':   
    #               'C2':
    #                  'trocas':   
    #                  'comparacoes':   
    #                  'tempo':   
    #               'C3':
    #                  'trocas':   
    #                  'comparacoes':   
    #                  'tempo':   
    #           'medio':
    #               'C1':
    #                  'trocas':   
    #                  'comparacoes':   
    #                  'tempo':   
    #               'C2':
    #                  'trocas':   
    #                  'comparacoes':   
    #                  'tempo':   
    #               'C3':
    #                  'trocas':   
    #                  'comparacoes':   
    #                  'tempo':   
    #           'grande':
    #               'C1':
    #               'C2':
    #               'C3':
    #           'supergrande':
    #               'C1':
    #               'C2':
    #               'C3':

def random_vetor():
    return np.random.randint(0, 100, 100) 

def criar_vetores():
    vetores = {}
    for vetor_path in os.listdir(PATH):
        _, tail = os.path.split(vetor_path)
        with open(PATH+'\\'+vetor_path, 'r') as f:
            vetor = np.array(list(map(int, f.read().split('\n'))))
            vetores[tail[:-4]] = vetor
    return vetores


if __name__ == '__main__':
    main()