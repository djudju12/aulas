import ipywidgets as widgets
from IPython.display import display
from utilidades import * 
import timeit

COL_DESC = 0
COL_VALOR = 1
COL_ESTOQUE = 2
# 
# value = cadastrados[EDITAR_DESC.value][COL_VALOR] if EDITAR_DESC.value is not None else 0,
# value = cadastrados[EDITAR_DESC.value][COL_ESTOQUE] if EDITAR_DESC.value is not None else 0,

# -------------- EDITAR --------------- #
EDITAR_DESC = widgets.Dropdown(
            disabled=False,
            description = 'Descrição'
          )

EDITAR_VALOR_UN = widgets.FloatText(
                  description = 'Valor unitário:',
                  disabled = True)

EDITAR_ESTOQUE = widgets.IntText( 
            description = 'Estoque:',
            placeholder = 0,
            disabled = True
          )

EDITAR = widgets.Button(
            description = 'Editar',
            tooltip = 'Habilitar edição',
          )

SALVAR = widgets.Button(
            description = 'Salvar',
            tooltip = 'Salvar alterações',
            disabled = True,
            button_style = 'success',
          )

EXCLUIR = widgets.Button(
            description = 'Excluir',
            tooltip = 'Excluir registro',
            disabled = True,
            button_style ='danger',
          )

# -------------- CADASTRAR --------------- #
DESCRICAO = widgets.Text(
              value = '',
              placeholder = 'Descrição',
              description = 'Descrição:' 
          )

VALOR_UN = widgets.FloatText(
            placeholder = 0.0,
            description = 'Valor unitário:'
           )

ESTOQUE = widgets.IntText(
            description='Estoque:',
            placeholder = 0
          )

CADASTRAR = widgets.Button(
            description='Cadastrar',
            tooltip='Cadastrar alimento',
          )

# -------------- FUNCS --------------- #
def time_it(func):
  def wrapper(*args, **kwargs):
    execs = 100000
    t = timeit.timeit(lambda: func(*args, **kwargs), number=execs)
    return print(f"Tempo de {execs} execuções => {t:.3f} segundos")
  return wrapper


def cad_click(b, dados):
  dados.append([DESCRICAO.value, VALOR_UN.value, ESTOQUE.value])
  DESCRICAO.value = '' 
  VALOR_UN.value = 0 
  ESTOQUE.value = 0

def habilitar_edicao():
  habilitar_widgets((EDITAR_VALOR_UN, EDITAR_ESTOQUE, SALVAR, EXCLUIR))
  desabilitar_widgets((EDITAR_DESC, EDITAR))

def desabilitar_edicao():
  desabilitar_widgets((EDITAR_VALOR_UN, EDITAR_ESTOQUE, SALVAR, EXCLUIR))
  habilitar_widgets((EDITAR_DESC, EDITAR))

def on_change_desc(change, dados):
  if on_change(change):
    index = EDITAR_DESC.value if EDITAR_DESC.value is not None else 0 
    if len(dados) > 1:
      ajusta_campos([
          (EDITAR_VALOR_UN, COL_VALOR), 
          (EDITAR_ESTOQUE, COL_ESTOQUE)
          ], dados, index)
    else:
      EDITAR_VALOR_UN.value = 0
      EDITAR_ESTOQUE.value = 0

def botao_EDITAR(botao, dados):
  if len(dados) == 0:
    print('Lista vazia!')
  elif novo_item(dados, EDITAR_DESC.options):
    print('Você possui itens novos na lista.\nAtualize a célula para continuar!')
  else:
    habilitar_edicao()

def salvar_edicao(botao, dados):
  desabilitar_edicao()
  index = EDITAR_DESC.value
  dados[index][COL_VALOR] = EDITAR_VALOR_UN.value 
  dados[index][COL_ESTOQUE] = EDITAR_ESTOQUE.value 

def excluir_registro(botao, dados):
  desabilitar_edicao()
  index = EDITAR_DESC.value
  del dados[index] 
  EDITAR_DESC.options = dropdown_options(dados, COL_DESC)
  if len(dados) == 0:
    EDITAR_VALOR_UN.value = 0
    EDITAR_ESTOQUE.value = 0
  else:
    ajusta_campos([
        (EDITAR_VALOR_UN, COL_VALOR), 
        (EDITAR_ESTOQUE, COL_ESTOQUE)
        ], dados, 0)

SALVAR.on_click(lambda: salvar_edicao(b, cadastrados))
EXCLUIR.on_click(excluir_registro)
EDITAR_DESC.observe(on_change_desc)
