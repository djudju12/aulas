#include <stdio.h>

void bad_incr(int* ptr) {
    (*ptr)++;
}

void lock_incr(int* ptr) {
    asm(
        "lock\n\t"
        "addl $1,%[p]\n\t"
        : [p] "+m" (*ptr)
    );
}

int main(void) {
    int t1 = 0;
    int t2 = 0;
    for (int i = 0; i < 10; i++) {
        lock_incr(&t1);
        bad_incr(&t2);
    }
    printf("%d %d\n", t1, t2);
}