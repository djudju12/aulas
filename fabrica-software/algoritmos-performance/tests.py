import numpy as np
from numpy import random as rd

SIZE_T = 50 
SIZE_M = 500
SIZE_G =  1_000
MAX_VALUE = 1_000
MIN_VALUE = 0
DUP_VALUE = 100
PERC_DUPS = 80 

# Aleatoria pequena 
def rand_array(size: int) -> np.ndarray:
    return np.array(rd.randint(MIN_VALUE, MAX_VALUE, size))

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
    arr = np.array(rd.randint(MIN_VALUE, MAX_VALUE, size))
    arr[rd.choice(SIZE_M, int(size*PERC_DUPS/100), replace=False)] = DUP_VALUE
    return arr

if __name__ == '__main__':
    tiny_array = rand_array(SIZE_T)
    big_array = rand_array(SIZE_G)
    ordered_array = ordered(SIZE_M)
    reversed_array = reversed(SIZE_M)
    duplicated_array = duplicated(SIZE_M)
    lots_of_dups_array = lots_of_duplicateds(SIZE_M)
    empty_array = zero_elements()
    one_element_array = one_element()

    