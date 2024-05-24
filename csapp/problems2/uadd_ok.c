#include <stdio.h>

int uadd_ok(unsigned x, unsigned y) {
    return (x + y) >= x;
}

int main(void) {
    unsigned umax = 1u << (sizeof(umax)*8) - 1;
    printf("%d\n", uadd_ok(umax/4, umax));
    return 0;
}