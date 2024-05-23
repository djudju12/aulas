#include <stdio.h>
#include <string.h>
#include <inttypes.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
    int i;
    for (int i = 0; i < len; ++i) {
        printf(" %.2x", start[i]);
    }
    printf("\n");
}

void show_int(int x) {
    show_bytes((byte_pointer) &x, sizeof(x));
}

void show_float(float x) {
    show_bytes((byte_pointer) &x, sizeof(x));
}

void show_pointer(void *x) {
    show_bytes((byte_pointer) &x, sizeof(x));
}

int div16(uint32_t x) {
    // k | x => 0000 0000 0000 0000 0000 0000 0000 1111
    // unsigned bias = ((x >> 31) & 0x1) * 15; // minha solução (pior)
    int bias = (x >> 31) & 0xF; // solucao do livro
    return (x + bias) >> 4;
}

int main(void) {
    printf("%d\n", div16(-32));
    return 0;

    // int val = 0x87654321;
    // byte_pointer valp = (byte_pointer) &val;
    // show_bytes(valp, 1);           // -> 0x21
    // show_bytes(valp, 2);           // -> 0x2143
    // show_bytes(valp, 3);           // -> 0x214365
    // show_bytes(valp, sizeof(val)); // -> 0x21436587

    // int val2 = 3510593;
    // show_int(val2);
    // show_float((float) val2);

    // const char *s = "abcdef";
    // show_bytes((byte_pointer) s, strlen(s));
    // return 0;
}