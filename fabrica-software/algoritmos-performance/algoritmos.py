from bisect import bisect_left
import numpy as np


def insertion_sort(vetor):
    for i in range(1, len(vetor)):
        chave = vetor[i]
        # bisect_left eh uma funcao built-in python
        # que retorna o index onde o valor CHAVE
        # deve ser inserido no vetor de forma que a ordem seja mantida
        j = bisect_left(vetor, chave, 0, i)
        # Empurramos o restante do vetor para a direita e inserimos o valor
        vetor[j+1:i+1] = vetor[j:i]
        vetor[j] = chave               # CHAVE na posicao correta
    return vetor

<<<<<<< HEAD
def bubble_sort(vetor):           # Bolha com melhor desempenho   
  n = len(vetor)                   # Verifica tamanho do vetor.     
  troca = True                     # Troca é uma flag que avisa quando o vetor está ordenado (melhor desempenho).
  while troca:                     # Enquanto houver troca, continua.  
    troca = False                  # Considera que troca pode não ocorrer.
    for i in range(n-1):           # Percorre para o final do vetor.
      if vetor[i] > vetor[i+1]:    # Verifica se a troca é necessária.
        vetor[i], vetor[i+1] = vetor[i+1], vetor[i]  # Realiza a troca.
        troca = True               # Sinaliza que houve troca. 
    n -= 1                         # Ajusta o tamanho do vetor a ser percorrido.   
  return vetor
=======
>>>>>>> 152dfaee175121eb32c9644156f4af8bf33b6718

def bubble_sort(vetor):           # Bolha com melhor desempenho
    n = len(vetor)                   # Verifica tamanho do vetor.
    # Troca é uma flag que avisa quando o vetor está ordenado (melhor desempenho).
    troca = True
    while troca:                     # Enquanto houver troca, continua.
        troca = False                  # Considera que troca pode não ocorrer.
        for i in range(n-1):           # Percorre para o final do vetor.
            if vetor[i] > vetor[i+1]:    # Verifica se a troca é necessária.
                vetor[i], vetor[i+1] = vetor[i+1], vetor[i]  # Realiza a troca.
                troca = True               # Sinaliza que houve troca.
        # Ajusta o tamanho do vetor a ser percorrido.
        n -= 1
    return vetor


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

def merge_sort(vetor):
    def merge(esquerda, direita):
        resultado = np.array([], dtype=int)
        i = j = 0

        #Compara os elementos de esquerda e direita e adiciona o menor ao resultado
        while i < len(esquerda) and j < len(direita):
            if esquerda[i] < direita[j]:
                resultado = np.append(resultado, esquerda[i])
                i += 1
            else:
                resultado = np.append(resultado, direita[j])
                j += 1

        # Adiciona o restante dos elementos de esquerda ou direita ao resultado
        resultado = np.append(resultado, esquerda[i:])
        resultado = np.append(resultado, direita[j:])
        return resultado
    
    # Verifica se o vetor tem tamanho 1 ou 0 e retorna o vetor caso afirmativo
    if len(vetor) <= 1:
        return vetor
    
    # Divide o vetor em duas partes iguais 
    meio = len(vetor) // 2
    esquerda = merge_sort(vetor[:meio])
    direita = merge_sort(vetor[meio:])
    
    # Mescla as duas partes ordenadas em um vetor único
    return merge(esquerda, direita)

def radix_sort(lista):
    if len(lista) == 0:
        return lista
    # determina o valor máximo e mínimo da lista
    valor_maximo = max(lista)
    valor_minimo = min(lista)

    # Cria uma lista com um índice para cada valor possívl na array, considerando os valores máximos e mínimos
    contadores = [0] * (valor_maximo - valor_minimo + 1)
    # Conta a ocorrência de cada valor na lista
    for valor in lista:
        contadores[valor - valor_minimo] += 1

    # Constrói a lista ordenada
    lista_ordenada = []
    for valor in range(valor_minimo, valor_maximo + 1):
        indice = valor - valor_minimo
        # Adiciona o valor na lista ordenada, o valor é adicionado de acordo com a quantidade de vezes que ele aparece na lista original
        lista_ordenada.extend([valor] * contadores[indice])

    return lista_ordenada

def shell_sort(vetor):
    gap = len(vetor) // 2                                                         #Define intervalo de distância entre os elementos
    while gap > 0:                                                                #While que continua executando até que gap seja 1
        for i in range(gap, len(vetor)):                                          #Percorre vetor, do gap até o fim
            temp = vetor[i]                                                       #Armazena valor atual e índice
            j = i
            while j >= gap and vetor[j - gap] > temp:                             #Compara o valor atual com o valor que está gap posições antes e realiza a troca de posição caso necessário
                vetor[j] = vetor[j - gap]
                j -= gap
            vetor[j] = temp                                                       #Insere o valor na posição correta
        gap //= 2                                                                 #Divide gap por 2 a cada iteração
    return vetor


def main():
    from numpy import random as rd

    # vector = rd.randint(0, 100, 10)
    vector = []
    print(radix_sort(vector))

if __name__ == '__main__':
    main()
