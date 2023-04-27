def receber_dados():
   a = int(input())
   b = int(input())
   return (a, b)

def impar(i):
   return i % 2 == 1

def percorrer(comeco, final):

   soma = 0
   while True:
      comeco = comeco + 1
      if comeco == final:
         break   
      if impar(comeco):
         soma += comeco
   return soma 

def main():
   range_t = receber_dados()
   print(percorrer(min(range_t), max(range_t)))


if __name__ == '__main__':
   main()