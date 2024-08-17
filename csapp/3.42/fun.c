#include <stdio.h>

struct ELE {
    long v;
    struct ELE *p;
};

long fun(struct ELE *ptr) {
    long c = 0
    while (ptr) {
        c += ptr->v;
        ptr = ptr->p;
    }
}

int main(void) {
    return 0;
}
