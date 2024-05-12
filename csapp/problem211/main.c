#include <stdio.h>

void inplace_swap(int *x, int *y) {
    *y = *x ^ *y;
    *x = *x ^ *y;
    *y = *x ^ *y;
}

void reverse_array(int a[], int cnt) {
    int first, last;
    for (first = 0,last = cnt-1; first < last; first++,last--) {
        inplace_swap(&a[first], &a[last]);
    }
}

int bis(int x, int m) {
    return x | m;
}

int bic(int x, int m) {
    return x & ~m;
}

int bool_or(int x, int y) {
    return bis(x, y);
}

int bool_xor(int x, int y) {
    return bis(bic(x, y), bic(y, x));
}

#define HAX_FMT "0x%.8x"
int main(void) {
    return 0;
    // A.
    int x = 0x87654321;
    printf("A. "HAX_FMT" & 0xFF = "HAX_FMT"\n", x, x & 0xFF);

    // B.
    // (~x & ~0xF) | x & 0xF
    // printf("A. "HAX_FMT" & 0xF = "HAX_FMT"\n", x, (~x & ~0xFF) | x & 0xFF);
    printf("A. "HAX_FMT" ^ ~0xFF = "HAX_FMT"\n", x, x ^ ~0xFF); // xor with 1 = inverse, xor with 0 = identity

    // C.
    printf("A. "HAX_FMT" | 0xFF = "HAX_FMT"\n", x, x | 0xFF);

    return 0;
    int a[] = { 1, 2, 3, 4 };
    int len = sizeof(a)/sizeof(a[0]);
    reverse_array(a, len);
    for (int i = 0; i < len; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");


    return 0;
}