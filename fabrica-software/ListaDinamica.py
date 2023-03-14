from typing import Any


class No:
   def __init__(self, valor: Any) -> None:
      self.valor = valor 
      self.proximo = None 

   def mostrar_no(self) -> None:
      print(self.valor)

class ListaEncadeada:
   def __init__(self) -> None:
      self.primeiro = None

   def lista_vazia(self) -> bool:
      return self.primeiro == None

   def inserir_inicio(self, valor: Any) -> None:
      novo = No(valor)
      novo.proximo = self.primeiro
      self.primeiro = novo

   def mostrar_lista(self) -> None:
      if self.lista_vazia():
         print("Lista vazia")
         return None 
      atual = self.primeiro
      while (atual != None):
         atual.mostrar_no()   
         atual = atual.proximo

   def inserir_fim(self, valor:Any) -> None:
      if self.lista_vazia():
         self.inserir_inicio(valor)
      else:
         atual = self.primeiro
         while (atual.proximo != None):
            atual = atual.proximo
         novo = No(valor)
         atual.proximo = novo
      

def main():
   lista = ListaEncadeada()
   lista.inserir_inicio(1)
   lista.inserir_inicio(2)
   lista.inserir_inicio(3)
   lista.inserir_fim(7)
   lista.inserir_fim(91)
   lista.inserir_inicio(41)
   lista.mostrar_lista()

if __name__ == '__main__':
   main()