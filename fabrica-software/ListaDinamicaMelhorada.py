from typing import Any


class No:
    def __init__(self, valor: Any) -> None:
        self.valor = valor
        self.proximo: No | None = None

    def mostrar_no(self) -> None:
        print(self.valor, end=" ")


class ListaEncadeada:
    def __init__(self) -> None:
        self.primeiro: No | None = None
        self.tail: No | None = None
        self.len: int = 0
        self.current: No = self.primeiro

    def __iter__(self) -> 'ListaEncadeada':
        self.current = self.primeiro
        return self
    
    def __next__(self) -> No:
        if self.current is None:
            raise StopIteration 
        else:
            retorno = self.current
            self.current = self.current.proximo 
            return retorno

    def lista_vazia(self) -> bool:
        return self.primeiro == None
    
    def mostrar_lista(self) -> None:
        if self.lista_vazia():
            print("Lista vazia")
            return None
        for item in self:
            item.mostrar_no()
        print("\n")

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
            novo = No(valor)
            self.tail.proximo = novo
            self.tail = novo
            self.len += 1

    def value_at(self, index: int) -> No:
        if self.lista_vazia() or index > self.len:
            raise IndexError
        elif index == self.len-1:
            return self.tail.valor
        else:
            count = 0
            for item in self:
                if count == index:
                    return item.valor
                count += 1

    def index_of(self, valor: Any) -> int:
        if self.lista_vazia():
            raise -1
        elif self.tail.valor == valor:
            return self.len-1
        else:
            count = 0
            for item in self:
                if item.valor == valor:
                    return count
                count += 1
        return -1

    def delete(self, index: int) -> None:
        if self.lista_vazia() or index > self.len-1:
            raise IndexError
        elif index == 0:
            self.primeiro = self.primeiro.proximo
        else:
            count = 0
            for item in self:
                if count == index-1:
                    item.proximo = item.proximo.proximo
                count += 1
        self.len -= 1

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
        elif index == self.len:
            self.inserir_fim(valor)
        else:
            no_valor = No(valor)
            count = 0
            for item in self:
                if count == index-1:
                    no_valor.proximo = item.proximo
                    item.proximo = no_valor 
                    self.len += 1 
                    return 
                count += 1


    def naive_sort(self) -> 'ListaEncadeada':
        atual = self.primeiro
        sorted_list = ListaEncadeada()
        sorted_list.inserir_inicio(atual.valor)
        sorted_list.inserir_inicio(self.primeiro)

        for n in range(1, self.len):
            proximo = sorted_list.primeiro
            atual = self.value_at(n)
            index = 0
            inserted = False
            while (atual > proximo.valor):
                if proximo.proximo is None:
                    sorted_list.inserir_fim(atual) 
                    inserted = True
                    break
                proximo = proximo.proximo
                index += 1

            if not inserted:
                sorted_list.inserir_at(index, atual)

        return sorted_list








def main():

    return 0


if __name__ == '__main__':
    main()
