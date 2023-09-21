from typing import Callable
from inspect import signature

# definições de primitivas 
def identidade(x: int) -> int:
    return x 

def sucessor(x: int) -> int:
    return x + 1 

def projecao(tup: tuple, i: int) -> int:
    if len(tup) <= i:
        print(f"Index {i} out of range")

    return tup[i] 

# definição da soma através da noção formal de funções recursivas de Kleene
def soma(x: int, y: int) -> int:
    if y == 0:
        return x
    
    return projecao((x, y-1, sucessor(soma(x, y-1))), 2)


# definição da multiplicação através da noção formal de funções recursivas de Kleene
def mult(x: int, y: int) -> int:
    if y == 0:
        return 0 
    
    return soma(mult(x, y-1), x)

def fatorial(x: int) -> int:
    if x == 0:
        return sucessor(0)
    
    return mult(fatorial(x-1), sucessor(x-1))

def test(fun: Callable, expected, *args) -> None:
    result = fun(*args) 
    if result != expected:
        print(f"[ RUN ] {fun.__name__}{args} >>> {result} != {expected} [ FAIL ]")
    else:
        print(f"[ RUN ] {fun.__name__}{args} >>> {result} == {expected} [ PASS ]")

def main():
    test(soma, 4, 2, 2)
    test(soma, 6, 2, 4)
    test(mult, 4, 2, 2)
    test(mult, 6, 2, 3)
    test(fatorial, 1, 0)
    test(fatorial, 2, 2)
    test(fatorial, 6, 3)

    

if __name__ == '__main__':
    main()