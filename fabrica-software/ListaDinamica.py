from typing import Any


class No:
    def __init__(self, valor: Any) -> None:
        self.valor = valor
        self.proximo: No | None = None

    def mostrar_no(self) -> None:
        print(self.valor)


class ListaEncadeada:
    def __init__(self) -> None:
        self.primeiro: No | None = None
        self.tail: No | None = None
        self.len: int = 0

    def lista_vazia(self) -> bool:
        return self.primeiro == None
    
    def mostrar_lista(self) -> None:
        if self.lista_vazia():
            print("Lista vazia")
            return None
        atual = self.primeiro
        while (atual != None):
            atual.mostrar_no()
            atual = atual.proximo

    def inserir_inicio(self, valor: Any) -> None:
        novo = No(valor)
        novo.proximo = self.primeiro
        self.primeiro = novo
        self.len += 1
        if self.len == 1:
            self.tail = self.primeiro

    def inserir_fim(self, valor: Any) -> None:
        if self.lista_vazia():
            self.inserir_inicio(valor)
        else:
            atual = self.primeiro
            while (atual.proximo != None):
                atual = atual.proximo
            novo = No(valor)
            atual.proximo = novo
            self.tail = novo
            self.len += 1

    def value_at(self, index: int) -> No:
        if self.lista_vazia() or index > self.len:
            raise IndexError
        elif index == self.len-1:
            return self.tail.valor
        elif index == 0:
            return self.primeiro.valor
        else:
            count = 1
            atual = self.primeiro.proximo
            while (count < self.len-1):
                if count == index:
                    return atual.valor
                else:
                    atual = atual.proximo
                    count += 1

    def index_of(self, valor: Any) -> int:
        if self.lista_vazia():
            raise IndexError
        atual = self.primeiro
        count = 0
        while (atual != None):
            if atual.valor == valor:
                return count
            atual = atual.proximo
            count += 1
        raise IndexError

    def delete(self, index: int) -> None:
        if self.lista_vazia() or index > self.len-1:
            raise IndexError
        elif index == 0:
            self.primeiro = self.primeiro.proximo
            self.len -= 1
        else:
            atual = self.primeiro
            count = 0
            while (count < index-1):
                atual = atual.proximo
                count += 1
            atual.proximo = atual.proximo.proximo

    def concat(self, element: Any ):
        if isinstance(element, ListaEncadeada):
            self.tail.proximo = element.primeiro
        elif isinstance(element, No):
            self.tail.proximo = element
        else:
            raise ValueError

    def inserir_at(self, index: int, valor: Any) -> None:
        if self.lista_vazia() or index > self.len-1:
            raise IndexError
        elif index == 0:
            self.inserir_inicio(valor)
        elif index == self.len-1:
            self.inserir_fim(valor)
        else:
            no_valor = No(valor)
            atual = self.primeiro
            count = 0
            while (count < index-1):
                atual = atual.proximo
                count += 1
            no_valor.proximo = atual.proximo
            atual.proximo = no_valor
            self.len += 1

    def naive_sort(self):
        atual = self.primeiro
        sorted_list = ListaEncadeada()
        sorted_list.inserir_inicio(atual.valor)

        for _ in range(1, self.len-1):
            atual = atual.proximo
            proximo = sorted_list.primeiro
            index = 0
            while (atual.valor > proximo.valor):
                if proximo.proximo is None:
                    sorted_list.inserir_fim(atual.valor) 
                proximo = proximo.proximo
                index += 1

            sorted_list.inserir_at(index, atual.valor)
            



def main():
    lista = ListaEncadeada()
    lista.inserir_inicio(1)
    lista.inserir_inicio(4)
    lista.inserir_inicio(3)
    lista.inserir_fim(7)
    lista.inserir_fim(75)
    lista.inserir_inicio(5)

    lista.mostrar_lista()
    print("\n")
    lista.naive_sort()
    lista.mostrar_lista()


if __name__ == '__main__':
    main()
