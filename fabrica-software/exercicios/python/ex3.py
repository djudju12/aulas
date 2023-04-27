
def impar(n: int) -> bool:
   return n % 2 == 1

def print_imp(n: int) -> None:
   for i in range(n+1):
      if impar(i):
         print(i)
      
def main():
   dado = int(input())
   print_imp(dado)

if __name__ == '__main__':
   main()