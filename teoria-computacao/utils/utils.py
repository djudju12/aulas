#!/bin/bash /usr/bin/python3
def codificar_tupla(a: tuple[4]) -> int:
    return (2**a[0])*(3**a[1])*(5**a[2])*(7**a[3])

def decodificar_natural(a: int) -> tuple:
    primes = [2, 3, 5, 7]
    result = {"2":0, "3":0, "5":0, "7":0}
    current = a
    count = 0
    for prime in primes:
        while current%prime == 0:
            count += 1    
            current /= prime
        
        result[str(prime)] = count
        count = 0

    if current != 1.0:
        return ()
    
    return (result["2"], result["3"], result["5"], result["7"])

def eh_monolitico(a: int) -> bool:
    d = decodificar_natural(a)
    if d[0] != 0 and d[0] != 1:
        return False

    if d[0] == 0:
        return d[3] == d[2]

    return True 

def assert_equal(a, b):
    if a == b:
        print(f"[SUCC] {a} == {b}")
    else:
        print(f"[FAIL] {a} != {b}")

def main():
    print("\n_Codificação")
    assert_equal(3675, codificar_tupla((0, 1, 2, 2)))
    assert_equal(5250, codificar_tupla((1, 1, 3, 1)))
    assert_equal(13505625, codificar_tupla((0, 2, 4, 4)))
    assert_equal(1512630, codificar_tupla((1, 2, 1, 5)))
    print("\n_Decodificação")
    assert_equal(decodificar_natural(3675), (0, 1, 2, 2))
    assert_equal(decodificar_natural(5250), (1, 1, 3, 1))
    assert_equal(decodificar_natural(13505625), (0, 2, 4, 4))
    assert_equal(decodificar_natural(1512630), (1, 2, 1, 5))
    print("\n_Checagem se um natural pode ser um programa monolitoco")
    assert_equal(eh_monolitico(525), False)
    assert_equal(eh_monolitico(210), True)
    assert_equal(eh_monolitico(450), True)
    assert_equal(eh_monolitico(750), True)
    assert_equal(eh_monolitico(315), True)

if __name__ == '__main__':
    main()