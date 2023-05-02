# Utilizar estas funcões para calcular quantidade de comparações e mudanças
from functools import wraps
from timeit import timeit

def time_it(func):
    @wraps(func)
    def timeit_wrapper(*args, **kwargs):
        t = timeit(lambda: func(*args, **kwargs), number=1)
        return t 
    return timeit_wrapper


def quick_sort_counting(array):
    comparisons = 0
    changes = 0
    sortedArray, comparisons, changes = quickorter_counting(
        array, 0, len(array)-1, comparisons, changes)
    return sortedArray, comparisons, changes


def particao_counting(array, first, last):
    comparisons = 0
    changes = 0

    # Utiliza o primeiro item do array como pivo
    pivot = array[first]

    # Utiliza o segundo item da lista como ponteiro menor, e ultimo item da lista como maior ponteiro
    low = first + 1
    high = last

    while True:

        # Percorre o array até encontrar um valor maior ou igual ao nosso pivo
        while low <= high and array[low] <= pivot:
            low += 1
            comparisons += 1

        # Percorre o array até encontrar um valor menor ou igual ao nosso pivo
        while low <= high and array[high] >= pivot:
            high -= 1
            comparisons += 1

        # Caso os ponteiros tenham se encontrado quebra o loop
        if high < low:
            break
        # Caso os ponteiros não tenham se encontrado, inverte os valores que eles estão apontando e continua o loop
        else:
            array[low], array[high] = array[high], array[low]
            changes += 1

    # Inverte o pivo com o valor do maior ponteiro, colocando ele em seu local definitivo
    array[first], array[high] = array[high], array[first]
    changes += 1
    # Retorna o valor do maior ponteiro para ser usado no dividir o array em dois
    return high, comparisons, changes


def quick_sort_counting(array, first, last, comparisons, changes):
    # Continua ordenando a lista enquanto o ponteiro passado para a função não se encontrarem
    if first < last:
        # Procura o local para dividir e organizar a lista
        split, comparisons, changes = particao_counting(array, first, last)

        # Divide a lista em duas partes para organizar seus elementos
        split_left = quickorter_counting(
            array, first, split - 1, comparisons, changes)
        split_right = quickorter_counting(
            array, split + 1, last, comparisons, changes)

        # Soma as mudanças e comparações antes de retornar o valor
        comparisons += split_left[1] + split_right[1]
        changes += split_left[2] + split_right[2]

    return array, comparisons, changes


def particao(array, first, last):
    # Utiliza o primeiro item do array como pivo
    pivot = array[first]

    # Utiliza o segundo item da lista como ponteiro menor, e ultimo item da lista como maior ponteiro
    low = first + 1
    high = last

    while True:

        # Percorre o array até encontrar um valor maior ou igual ao nosso pivo
        while low <= high and array[low] <= pivot:
            low += 1

        # Percorre o array até encontrar um valor menor ou igual ao nosso pivo
        while low <= high and array[high] >= pivot:
            high -= 1

        # Caso os ponteiros tenham se encontrado quebra o loop
        if high < low:
            break
        # Caso os ponteiros não tenham se encontrado, inverte os valores que eles estão apontando e continua o loop
        else:
            array[low], array[high] = array[high], array[low]

    # Inverte o pivo com o valor do maior ponteiro, colocando ele em seu local definitivo
    array[first], array[high] = array[high], array[first]
    # Retorna o valor do maior ponteiro para ser usado no dividir o array em dois
    return high

@time_it
def quick_sort(array, first=0, last=None):
    # Continua ordenando a lista enquanto o ponteiro passado para a função não se encontrarem
    if last is None:
        last = len(array)-1
        
    if first < last:
        # Procura o local para dividir e organizar a lista
        split = particao(array, first, last)

        # Divide a lista em duas partes para organizar seus elementos
        quick_sort(array, first, split - 1)
        quick_sort(array, split + 1, last)

    return array

@time_it
def selection_sort(arr):
    for i in range(len(arr)):  # Itera sobre o array
        # Define o índice do elemento mínimo como o índice atual da iteração
        min_index = i
        # Itera sobre os elementos do array à direita do elemento atual
        for j in range(i+1, len(arr)):
            # Se o elemento atual for maior que o próximo elemento à direita, atualiza o índice do elemento mínimo
            if arr[j] < arr[min_index]:
                min_index = j
        # Troca o elemento atual pelo elemento mínimo
        arr[i], arr[min_index] = arr[min_index], arr[i]
    return arr  # Retorna o array ordenado

def selection_sort_counting(arr):
    for i in range(len(arr)):  # Itera sobre o array
        # Define o índice do elemento mínimo como o índice atual da iteração
        min_index = i
        # Itera sobre os elementos do array à direita do elemento atual
        for j in range(i+1, len(arr)):
            # Se o elemento atual for maior que o próximo elemento à direita, atualiza o índice do elemento mínimo
            if arr[j] < arr[min_index]:
                min_index = j
        # Troca o elemento atual pelo elemento mínimo
        arr[i], arr[min_index] = arr[min_index], arr[i]
    return arr  # Retorna o array ordenado


