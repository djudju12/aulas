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

