#include <stdio.h>
#include <string.h>

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

int main(void) {
    // int val = 0x87654321;
    // byte_pointer valp = (byte_pointer) &val;
    // show_bytes(valp, 1);           // -> 0x21
    // show_bytes(valp, 2);           // -> 0x2143
    // show_bytes(valp, 3);           // -> 0x214365
    // show_bytes(valp, sizeof(val)); // -> 0x21436587

    // int val2 = 3510593;
    // show_int(val2);
    // show_float((float) val2);

    const char *s = "abcdef";
    show_bytes((byte_pointer) s, strlen(s));
    return 0;
}