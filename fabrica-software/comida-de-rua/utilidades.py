import pandas as pd
from ListaEncadeada import *

def desabilitar_widgets(widgets):
  for widget in widgets:
    widget.disabled = True

def habilitar_widgets(widgets):
  for widget in widgets:
    widget.disabled = False

def lista_vazia(lista):
  return len(lista) < 1

def ajusta_campos(campos, dados, index_linha):
  for campo, index_coluna in campos:
    campo.value = dados[index_linha][index_coluna]

def time_it(func):
  def wrapper(*args, **kwargs):
    execs = 100000
    t = timeit.timeit(lambda: func(*args, **kwargs), number=execs)
    return print(f"Tempo de {execs} execuções => {t:.3f} segundos")
  return wrapper

def on_change(change):
  return change['type'] == 'change' and change['name'] == 'value'

def novo_item(dados_atuais, dados_antigos):
  return len(dados_atuais) != len(dados_antigos)

def dropdown_options(cadastrados, col_desc):
  return [(cadastro[col_desc], index)  for index, cadastro in enumerate(cadastrados)]