#include <stdio.h>
#include <string.h>
#include <inttypes.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
    int i;
    for (int i = 0; i < len; ++i) {
        if (i > 0) {
            printf(" ");
        }
        printf("%.2x", start[i]);
    }
    printf("\n");
}

void show_bytes2(byte_pointer start, size_t len) {
    int i;
    printf("0x");
    for (int i = 0; i < len; ++i) {
        printf("%.2x", start[i]);
    }
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

int fun1(unsigned word) {
    return (int) ((word << 24) >> 24);
}

int fun2(unsigned word) {
    return ((int) word << 24) >> 24;
}

int div16(uint32_t x) {
    // k | x => 0000 0000 0000 0000 0000 0000 0000 1111
    // unsigned bias = ((x >> 31) & 0x1) * 15; // minha solução (pior)
    int bias = (x >> 31) & 0xF; // solucao do livro
    return (x + bias) >> 4;
}

int main(void) {
    unsigned ws[] = {
        0x00000076,
        0x87654321,
        0x000000C9,
        0xEDCBA987
    };

    printf("|     w      |  fun1(w)   |  fun2(w)   |\n");
    printf("|------------|------------|------------|\n");
    unsigned w;
    for (int i = 0; i < sizeof(ws)/sizeof(unsigned); i++) {
        w = ws[i];
        printf("| 0x%.8X | ", w);
        int x1 = fun1(w);
        show_bytes2((byte_pointer)&x1, sizeof(int));
        printf(" | ");
        int x2 = fun2(w);
        show_bytes2((byte_pointer)&x2, sizeof(int));
        printf(" |");
        printf("\n");
    }

    return 0;
    // short sx = -12345;
    // unsigned short usx = sx;
    // int x = sx;
    // unsigned ux = usx;

    // printf("sx = %d:\t", sx);
    // show_bytes((byte_pointer) &sx, sizeof(short));
    // printf("usx = %u:\t", usx);
    // show_bytes((byte_pointer) &usx, sizeof(unsigned short));
    // printf("x   = %d:\t", x);
    // show_bytes((byte_pointer) &x, sizeof(int));
    // printf("ux  = %u:\t", ux);
    // show_bytes((byte_pointer) &ux, sizeof(unsigned));
    // return 0;
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