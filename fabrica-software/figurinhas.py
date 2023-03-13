# Ricardo e Vicente são aficionados por figurinhas. Nas horas vagas, eles arrumam 
# um jeito de jogar um “bafo” ou algum outro jogo que envolva tais figurinhas.
# Ambos também têm o hábito de trocarem as figuras repetidas com seus amigos e 
# certo dia pensaram em uma brincadeira diferente. Chamaram todos os amigos e 
# propuseram o seguinte: com as figurinhas em mãos, cada um tentava fazer uma 
# troca com o amigo que estava mais perto seguindo a seguinte regra: cada um 
# contava quantas figurinhas tinha. Em seguida, eles tinham que dividir as 
# figurinhas de cada um em pilhas do mesmo tamanho, no maior tamanho que fosse 
# possível para ambos. Então, cada um escolhia uma das pilhas de figurinhas 
# do amigo para receber. Por exemplo, se Ricardo e Vicente fossem trocar as 
# figurinhas e tivessem respectivamente 8 e 12 figuras, ambos dividiam todas 
# as suas figuras em pilhas de 4 figuras (Ricardo teria 2 pilhas e Vicente 
# teria 3 pilhas) e ambos escolhiam uma pilha do amigo para receber.

# Entrada
# A primeira linha da entrada contém um único inteiro N (1 ≤ N ≤ 3000), indicando o 
# número de casos de teste. Cada caso de teste contém 2 inteiros F1 (1 ≤ F1 ≤ 1000) 
# e F2 (1 ≤ F2 ≤ 1000) indicando, respectivamente, a quantidade de figurinhas que 
# Ricardo e Vicente têm para trocar.

# Saída
# Para cada caso de teste de entrada haverá um valor na saída, representando o 
# tamanho máximo da pilha de figurinhas que poderia ser trocada entre dois jogadores.

# Exemplo de Entrada	Exemplo de Saída
# 3                             
# 8 12                       4   
# 9 27                       9   
# 259 111                    37

Caso = tuple[int, int]

def main() -> int:
   teste = int(input())
   casos = receber_input(teste)
   results = calcular_pilhas(casos)
   print_result(results)

   return 0

def receber_input(testes: int) -> list[Caso]:
   casos = [input().split() for _ in range(testes)]
   tuple_str2int = lambda x: tuple(map(int, x))
   return [tuple_str2int(caso) for caso in casos]

def calcular_pilhas(casos: list[Caso]) -> list:
   return [mdc(caso) for caso in casos]

# Não há necessidade de validar /0 pois o problema especifica que F1, F2 > 0
def mdc(caso: Caso) -> int:
   a, b = caso
   r = a % b 
   if (r == 0):
      return b
   else:
      return mdc((b, r))
   
def print_result(results: list) -> None:
   [print(result) for result in results]

if __name__ == '__main__':
   main()
