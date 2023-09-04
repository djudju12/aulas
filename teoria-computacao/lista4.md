### Programa P:

- 1: (F, 2), (ciclo, w) 
- 2: (G, 3), (G, 3) 
- 3: (F, 4), (parada, &)
- 4: (ciclo, w), (F, 2) 
- w: (ciclo, w), (ciclo, w)

A = {1, 2, 3, 4, &} _não tira nada_ 

### Programa Q:

- 6: (F, 7), (ciclo, w)
- 7: (G, 8), (G, 8)
- 8: (F, 9), (parada, &) 
- 9: (F, 7), (ciclow, w) 
- w: (ciclo, w), (ciclow, w)

A = {6, 7, 8, 9, &} _não tira nada_ 

### Determinar se Q == P

- 1: (F, 2), (ciclo, w) 
- 2: (G, 3), (G, 3) 
- 3: (F, 4), (parada, &)
- 4: (F, 2), (ciclo, w)
- **6:** (F, 7), (ciclo, w)
- 7: (G, 8), (G, 8)
- 8: (F, 9), (parada, &) 
- 9: (F, 7), (ciclow, w) 
- w: (ciclo, w), (ciclo, w)

B0 = {(1, 6)} Fortemente equivalentes

B1 = {(2, 7)} Fortemente equivalentes

B2 = {(3, 8)} Fortemente equivalentes

B3 = {(4, 9)} Fortemente equivalentes

**Q == P, ou seja, são equivalentes**