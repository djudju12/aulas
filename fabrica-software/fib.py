def fib(n: int, i: list) -> list:
   if n == 0:
      return 
   i.append(i[len(i)-1] + i[len(i)-2])
   fib(n-1, i)

def main() -> None:
   n = int(input())
   nfibs = [0, 1]
   fib(n-len(nfibs), nfibs)
   print(nfibs)

if __name__ == '__main__':
   main()