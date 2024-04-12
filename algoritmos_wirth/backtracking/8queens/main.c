#include <stdio.h>

typedef int boolean;

#define TRUE  1
#define FALSE 0

boolean x[8];
boolean a[8];
boolean b[15];
boolean c[15];

void init() {
    for (int i = 0; i < 8; i++) {
        x[i] = a[i] = TRUE;
    }

    for (int i = 0; i < 15; i++) {
        b[i] = c[i] = TRUE;
    }
}

boolean touch(int j, int i) {
    x[i] = j;
    a[j] = b[i+j] = c[i-j+7] = FALSE;
}

boolean rm(int j, int i) {
    a[j] = b[i+j] = c[i-j+7] = TRUE;
}

boolean isSafe(int j, int i) {
    return a[j] && b[i+j] && c[i-j+7];
}

void try(int i, boolean *q) {
    int j = -1;
    do {
        *q = FALSE; j++;
        if (isSafe(j, i)) {
            touch(j, i);
            if (i < 7) {
                try(i+1, q);
                if (*q == FALSE) {
                    rm(j, i);
                }
            } else {
                *q = TRUE;
            }
        }
    } while(*q != TRUE && (j < 8));
}

void try_all(int i) {
    for (int j = 0; j < 8; j++) {
        if (isSafe(j, i)) {
            touch(j, i);
            if (i < 7) {
                try_all(i + 1);
            } else {
                for (int k = 0; k < 8; k++) {
                    printf("%d ", x[k]+1);
                } printf("\n");
            }

            rm(j, i);
        }
    }
}

int main(void) {
    init();
    try_all(0);
    return 0;
    boolean q = FALSE;
    try(0, &q);
    printf("%d\n", q);
    for (int i = 0; i<8; i++) {
        printf("%d ", x[i]+1);
    } printf("\n");
    return 0;
}