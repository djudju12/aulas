## Questão 1:

### Monolito em C: 
```c

   #include <stdio.h>

   int F(int x) {
      int c = 0; 

      r1: 
         if (x == 0) goto r2;
         else {
            x--; c += 2; goto r1;
         }

      r2: 
         return c;
   }

   int main(void) {
      
      // subtraia de x
      // se x for == 0 então dobre 
      printf("%d", F(23));

   }
```

### Iterativo em Bash 
```bash
   #!/bin/bash
   c=0
   i=$1

   while [ $i -gt 0 ] 
   do 
      i=$((i - 1)) 
      c=$((c + 2)) 
   done

   echo "$c"#lang sicp 

   (define (F x);
      (define (G) (if (> x 0) (F (- x 1))))
      (define (H) (+ x x))
      (G);
      (H))

   (F 23) ; > 46
```

### Recursivo em lisp
```scheme
#lang sicp 

(define (F x);
   (define (G) (if (> x 0) (F (- x 1))))
   (define (H) (+ x x))
   (G);
   (H))

(F 23) ; > 46
```

## Questão 3:

