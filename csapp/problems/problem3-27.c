#include <stdio.h>

long fun_b(unsigned long x) {
    long val = 0;
    long i;
    for (i = 64; i != 0; i--) {
        val = (val << 1) | (x & 0x1);
        x >>= 1;
    }

    return val;
}

int main(void) {
    printf("%ld\n", fun_b(0xFFFFFFFFFFFFFFF0));
    printf("%ld\n", 0xFFFFFFFFFFFFFFF0);
    return 0;
}
