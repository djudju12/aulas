from bisect import bisect_left
from time import time


def insertion_sort_time(vetor):
    for i in range(1, len(vetor)):
        chave = vetor[i]
        j = bisect_left(vetor, chave, 0, i)
        vetor[j+1:i+1] = vetor[j:i]
        vetor[j] = chave
    return vetor


def bubble_sort_time(vetor):
    n = len(vetor)
    troca = True
    while troca:
        troca = False
        for i in range(n-1):
            if vetor[i] > vetor[i+1]:
                vetor[i], vetor[i+1] = vetor[i+1], vetor[i]
                troca = True
        n -= 1
    return vetor


def bubble_sort_comparacoes(vetor):
    comparacoes, trocas = 0, 0
    n = len(vetor)
    troca = True
    while troca:
        troca = False
        for i in range(n-1):
            comparacoes += 1
            if vetor[i] > vetor[i+1]:
                
                vetor[i], vetor[i+1] = vetor[i+1], vetor[i]
                trocas += 2
                
                troca = True
        n -= 1
    return comparacoes, trocas


def insertion_sort_comparasoes(vetor):
    comparacoes, trocas = 0, 0
    for i in range(1, len(vetor)):
        chave = vetor[i]

        j, c = bisect_left2(vetor, chave, 0, i)
        comparacoes += c

        trocas += 1
        vetor[j+1:i+1] = vetor[j:i]

        trocas += 1
        vetor[j] = chave

    return comparacoes, trocas


def bisect_left2(a, x, lo=0, hi=None):
    """Return the index where to insert item x in list a, assuming a is sorted.

    The return value i is such that all e in a[:i] have e < x, and all e in
    a[i:] have e >= x.  So if x already appears in the list, a.insert(i, x) will
    insert just before the leftmost x already there.

    Optional args lo (default 0) and hi (default len(a)) bound the
    slice of a to be searched.
    """
    comparacoes = 0


    comparacoes += 1
    if lo < 0:
        raise ValueError('lo must be non-negative')
    comparacoes += 1

    if hi is None:
        hi = len(a)

    while lo < hi:
        mid = (lo + hi) // 2
        comparacoes += 1
        if a[mid] < x:
            lo = mid + 1
        else:
            hi = mid

    return lo, comparacoes

def main():
    pass

if __name__ == '__main__':
    main()