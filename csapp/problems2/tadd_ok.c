#include <stdio.h>

int uadd_ok(unsigned x, unsigned y) {
    int sum = x + y;

    if (x < 0 && y < 0) {
        return sum < 0;
    }

    if (x >= 0 && y >= 0) {
        return sum >= 0;
    }


    return 1;
}

int main(void) {
    unsigned umax = 1u << (sizeof(umax)*8) - 1;
    printf("%d\n", uadd_ok(umax/4, umax));
    return 0;
}