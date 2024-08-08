// #define M 56
// #define N 40

// long P[M][N];
// long Q[N][M];

// long sum_element(long i, long j) {
// 	return P[i][j] + Q[j][i];
// }

#include <stdio.h>

#define N 1024

typedef int fix_matrix[N][N];

void fix_set_diag(fix_matrix A, int val) {
    for (long i = 0; i < N; i++) {
        A[i][i] = val;
    }
}

void fix_set_diag_opt(fix_matrix A, int val) {
    int *Astart = &A[0][0];
    int *Aend = &A[N][N];

    do {
        *Astart = val;
        Astart += N + 1;
    } while (Astart != Aend);
}


int main(void) {
    fix_matrix m = {0};
    fix_set_diag_opt(m, 3);
    for (long i = 0; i < N; i++) {
        for (long j = 0; j < N; j++) {
            printf("%01d ", m[i][j]);
        }
        printf("\n");
    }
}