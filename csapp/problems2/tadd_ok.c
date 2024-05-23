#include <stdio.h>

int tadd_ok(int x, int y) {
    int sum = x+y;
    int neg_overflow = x < 0 && y < 0 && sum >= 0;
    int pos_overflow = x >= 0 && y >= 0 && sum < 0;

    return !neg_overflow && !pos_overflow;
}

int tsub_ok(int x, int y) {
    return tadd_ok(x, -y);
}

int main(void) {
    int imin = 1u << ((sizeof(imin)*8) - 1);

    printf("%s\n", tsub_ok(-10, -imin) == 1 ? "true" : "false");
    return 0;
}