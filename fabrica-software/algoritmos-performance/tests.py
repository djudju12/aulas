import numpy as np
from numpy import random as rd
from algoritmos import *
from timeit import timeit

# ------ Configuraçoes dos arrays ------
# Tamanho do array
SIZE_T = 50 
SIZE_M = 500
SIZE_G =  1_000

# valor dos elementos do array
MAX_VALUE = 1_000
MIN_VALUE = 0
DUP_VALUE = 100 # valor dos duplcados
PERC_DUPS = 80  # porcentagem de duplicados 

# Algoritmos de teste. Adicione uma funcao aqui para incluir nos teste
ALGORITMOS = [insertion_sort, 
              selection_sort,
              merge_sort,
            #   quick_sort, # o grupo deixou a implementação privada
              radix_sort,
              shell_sort,
              bubble_sort,
            #   time 7 não achei
              ]

# Numero de testes executados na função TIMEIT
NUMBER_OF_TESTES = 1
# -------------------------------------

# Cria um dicionario com os arrays que serão ordenados
# Adicione aqui o novo array que deseja ordenar
def set_up_arrays() -> dict:
    arrays_to_sort = {}
    arrays_to_sort['tiny_array'] = rand_array(SIZE_T)
    arrays_to_sort['big_array'] = rand_array(SIZE_G)
    arrays_to_sort['ordered_array'] = ordered(SIZE_M)
    arrays_to_sort['reversed_array'] = reversed(SIZE_M)
    arrays_to_sort['duplicated_array'] = duplicated(SIZE_M)
    arrays_to_sort['lots_of_dups_array'] = lots_of_duplicateds(SIZE_M)
    arrays_to_sort['empty_array'] = zero_elements()
    arrays_to_sort['one_element_array'] = one_element()
    return arrays_to_sort

# Aleatoria pequena 
def rand_array(size: int) -> np.ndarray:
    return rd.randint(MIN_VALUE, MAX_VALUE, size)

# Crescente 
def ordered(size: int) -> np.ndarray:
    return np.sort(rand_array(size))

# Decrescente
def reversed(size: int) -> np.ndarray:
    return ordered(size)[::-1]

# Repetido
def duplicated(size: int) -> np.ndarray:
    return np.array([DUP_VALUE]*size)

# vazia
def zero_elements() -> list:
    return []

# um item
def one_element() -> list:
    return [DUP_VALUE]

# muitos repetidos
def lots_of_duplicateds(size: int) -> np.ndarray:
    arr = rd.randint(MIN_VALUE, MAX_VALUE, size)
    arr[rd.choice(SIZE_M, int(size*PERC_DUPS/100), replace=False)] = DUP_VALUE
    return arr

def main():
    # Cria os arrays inicais que serão ordenados
    arrays_to_sort = set_up_arrays()

    # Itera em cada os um algoritmos que estão no array     
    for algoritmo in ALGORITMOS:
        print(f'*Start of => {algoritmo.__name__}')
        # Ordena uma copia do array e printa o resultado
        for current_array in arrays_to_sort.keys():
            copied_array = arrays_to_sort[current_array].copy()
            time_to_print = timeit(lambda: algoritmo(copied_array), number=NUMBER_OF_TESTES)
            print(f'\ttime for {current_array} => {time_to_print:.10f}')

        print(f'*End of => {algoritmo.__name__}', end='\n\n')

if __name__ == '__main__':
    main()

