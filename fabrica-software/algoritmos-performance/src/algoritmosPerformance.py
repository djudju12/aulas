# Utilizar estas funcões para calcular quantidade de comparações e mudanças
from time import time

def selection_sort(arr):
    for i in range(len(arr)):
        min_index = i
        for j in range(i+1, len(arr)):
            if arr[j] < arr[min_index]:
                min_index = j
        arr[i], arr[min_index] = arr[min_index], arr[i]
    return arr 

def selection_count(arr):
    comparacoes = 0
    trocas = 0
    for i in range(len(arr)):
        min_index = i
        for j in range(i+1, len(arr)):
            comparacoes += 1
            if arr[j] < arr[min_index]:
                min_index = j
        trocas += 2
        arr[i], arr[min_index] = arr[min_index], arr[i]
    return comparacoes, trocas

def particao_for_counting(array, first, last):
    comparisons = 0
    changes = 0

    pivot = array[first]

    low = first + 1
    high = last

    while True:

        while low <= high and array[low] <= pivot:
            low += 1
            comparisons += 2

        while low <= high and array[high] >= pivot:
            high -= 1
            comparisons += 2

        comparisons += 1
        if high < low:
            break
        else:
            array[low], array[high] = array[high], array[low]
            changes += 2

    array[first], array[high] = array[high], array[first]
    changes += 2
    return high, comparisons, changes


def quick_count(array, first=0, last=None, comparisons=0, changes=0):

    comparisons += 1
    if last is None:
        last = len(array) - 1

    comparisons += 1
    if first < last:
        split, comparisons, changes = particao_for_counting(array, first, last)

        cl, tl = quick_count(
            array, first, split - 1, comparisons, changes)
        cr, tr = quick_count(
            array, split + 1, last, comparisons, changes)

        comparisons += cr + cl
        changes += tl + tr

    return comparisons, changes

def particao(array, first, last):
    pivot = array[first]

    low = first + 1

    while True:

        while low <= last and array[low] <= pivot:
            low += 1

        while low <= last and array[last] >= pivot:
            last -= 1

        if last < low:
            break
        else:
            array[low], array[last] = array[last], array[low]

    array[first], array[last] = array[last], array[first]
    return last

def quick_sort(array, first=0, last=None):
    if last is None:
        last = len(array) - 1

    if first < last:
        split = particao(array, first, last)

        quick_sort(array, first, split - 1)
        quick_sort(array, split + 1, last)

    return array 

def quick_time(array):
    time_s = time()
    array = quick_sort(array)
    return time() - time_s 

def selection_time(array):
    time_s = time()
    array = selection_sort(array)
    return time() - time_s 
