def sao_multiplos(dados: list) -> bool:
   return max(dados)%min(dados) == 0

def recebe_ints() -> list:
   return [int(input()) for _ in range(2)]

def main():
   inteiros = recebe_ints()
   if not any(inteiros):
      result = True
   else:
      result = sao_multiplos(inteiros)  
   print(result)
  
if __name__ == '__main__':
   main()