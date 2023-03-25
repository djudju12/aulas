from typing import Any

class No:
  def __init__(self, valor: Any) -> None:
    self.valor: Any = valor
    self.proximo: No | None = None

  def mostrar_no(self) -> None:
    print(self.valor, end=" ")


class ListaEncadeada:
  def __init__(self) -> None:
    self.primeiro: No | None = None
    self.len: int = 0
    self.current: No | None = self.primeiro
    self.tail: No | None = None

  def __iter__(self) -> 'ListaEncadeada':
    self.current = self.primeiro
    return self

  def __next__(self) -> No:
    if self.current is None:
      raise StopIteration 
    else:
      no_atual = self.current
      self.current = self.current.proximo 
      return no_atual.valor

  def mostrar_lista(self) -> None:
    if self.lista_vazia():
      print("Lista vazia")
      return None
    for item in self:
      print(item)
    print("\n")

  def lista_vazia(self) -> bool:
    return self.primeiro == None

  def inserir_inicio(self, valor: Any) -> None:
    novo = No(valor)
    novo.proximo = self.primeiro
    self.primeiro = novo
    if self.len == 0:
      self.tail = novo
    self.len += 1

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
    else:
      count = 0
      for item in self:
        if count == index:
          return item
        count += 1

  def delete(self, index: int) -> None:
    if self.lista_vazia() or index > self.len-1:
      return print('Index fora dos limites da lista')
    elif index == 0:
      self.primeiro = self.primeiro.proximo
    else:
      count = 0
      item = self.primeiro
      for _ in self:
        if count == index-1:
          item.proximo = item.proximo.proximo
          if index == self.len-1:
            self.tail = item
          break
        item = item.proximo
        count += 1
    self.len -= 1
