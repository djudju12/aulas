# Chapter 2 - Lexi

### Design Problemas

1. Document Structure
	Documentos são uma parte importante do software e como eles 
	serao representados afeta quase todos os outros componenents

2. Formatting
	Como os textos são colocados na tela

3. Embellishing the user interface
	O quao facil é adicionar e remover elementos da UI

4. Supporting multiple look-and-feel standards 
	Acredito que se trata de look and feel de diferentes sistemas.
	Motif define o tema visual e PM o controle da sjanelas, isso 
	pode e será diferente dependendo do sistema operacional. Talvez, 
	devido a grande padronização, hoje em dia isso não é tão falado

5. Supporting multiple window systems
	vai de encontro com o 4 

6. User operations 
	Garantir um mecanismo uniforme para interagir com o usuario 

7. Spelling checking and hyphenation 



### Patterns

1 -> Composite: 

	Compoẽ objetos em estruturas de arvores. Composite permite que 
	clientes tratem objetos individuais e objetos compostos uniform
	emente.
	
	A chave para o padrão Composite esta na classe abstrata que repre
	senta tanto os primitivos quanto seus containers. Para sistemas 
	grafáficos, essa classe seria o Graphic. Graphic declaração opera
	ções como Draw que são especifical de objetos gráficos. Também define
	operações que todos os objetos compostos compartilhas, como operações
	para acessar e administrar filhos. 
	
	Linhas, retangulos e textos definem objetos primitivos. Essas classes
	sabem como se desenhar, mas como não possuem filhos nenhuma delas imple
	menta filho-related operações. 
	
```
				aPicture --* aRec
				 /    \
			        /      \
                               *        *
			   aPicture	aLine
			       |
			       |	
		               *	
			     aLine
				
```

	Aplicação: Quando você deseja representar part-whole (nao inteiros?) objetos hierarquicos
		   Quando você quer que clientes nao precisem fazer a distinção de objetos indivi
		   duais e compostos


