from bisect import bisect_left

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

