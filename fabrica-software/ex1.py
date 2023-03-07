def recebe_ints(n: int) -> list:
	return [valid_input() for _ in range(n)]

def valid_input() -> int:
   nt = int(input())
   if nt > 10: 
      print("invalid input")
      return False
   else:
      return nt

def calc_media(notas: list) -> int:
	return notas[0]*0.2 + notas[1]*0.3 + notas[2]*0.5 

def main():
	notas = recebe_dados()
	if not any(notas):
		return False

	print(calc_media(notas))

if __name__ == '__main__':
    main()
