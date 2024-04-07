#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>

/*
    Dado um tabuleiro nxn, com n² campos. Um cavalo - que se move segundos as
    regras do xadrez - é colocado no campo com as coordenadas inciais x0 e y0.
    O problema a ser resolvido consistem em se encontrar uma forma de cobrir
    todo o tabuleiro, se é que existe de fato uma maneira de faze-lo, isto é
    de calcular um percurso n²-1 movimentos, tal que todas as células do tabu_
    leiro sejam percorridas exatamente uma vez.
*/

#define H_SIZE 8

int **tabuleiros;
int* tabuleiro_alloc() {
    return (int *) calloc(H_SIZE * H_SIZE, sizeof(int));
}

int dx[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
int dy[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

int x0, y0;

void tabuleiro_set(int *tabuleiro, int x, int y, int value) {
    int index = y * H_SIZE + x;
    tabuleiro[index] = value;
}

int tabuleiro_get(int *tabuleiro, int x, int y) {
    int index = y * H_SIZE + x;
    return tabuleiro[index];
}

int isAceitavel(int x1, int y1, int *tabuleiro) {
    return (y1 >= 0)
        && (y1 < H_SIZE)
        && (x1 >= 0)
        && (x1 < H_SIZE)
        && (tabuleiro_get(tabuleiro, x1, y1) == 0);
}

int try(int i, int x, int y, int *tabuleiro, int k0, int kf) {
    assert(kf <= H_SIZE && "k final cannot be greater than the number of plays");
    assert(k0 < H_SIZE && kf >= k0);
    int q1 = 0;
    for (int k = k0; k < kf && q1 != 1; k++) {
        int y1 = y + dy[k];
        int x1 = x + dx[k];
        if (isAceitavel(x1, y1, tabuleiro)) {
            tabuleiro_set(tabuleiro, x1, y1, i);
            if (i < H_SIZE*H_SIZE) {
                q1 = try(i+1, x1, y1, tabuleiro, 0, H_SIZE);
                if (q1 == 0) {
                    tabuleiro_set(tabuleiro, x1, y1, 0);
                }
            } else {
                q1 = 1;
            }
        }
    }

    return q1;
}

#define MAX_NUMBER_OF_THREADS 8
pthread_t threads[MAX_NUMBER_OF_THREADS];
int running[MAX_NUMBER_OF_THREADS];
atomic_int t_running;
long number_of_running_threads;

void* async_try(void *arg) {
    int i = atomic_fetch_add(&t_running, 1);
    int dk = *((int *) arg);

    int *tabuleiro = tabuleiros[i];
    tabuleiro_set(tabuleiro, x0, y0, 1);

    int q = try(2, x0, y0, tabuleiro, i*dk, (i*dk)+dk);

    printf("[ %d ] (%d..%d) %d\n", i, i*dk, (i*dk)+dk, q);
    running[i] = q;
    return NULL;
}

/*
    return true when still searching
    if (cnt_of_finished_tasks < number_of_running_threads) => true
    if (cnt_of_finished_tasks == number_of_running_threads) => false
    if (path_are_finded) => false

*/
int path_not_finded_or_tasks_are_running() {
    int cnt_of_finished_tasks = 0;
    for (int i = 0; i < number_of_running_threads; i++) {
        if (running[i] == 1) return 0;
        if (running[i] == 0) cnt_of_finished_tasks++;
    }

    return cnt_of_finished_tasks < number_of_running_threads;
}

void run_threads() {
    t_running = ATOMIC_VAR_INIT(0);
    number_of_running_threads = sysconf(_SC_NPROCESSORS_ONLN);

    if (number_of_running_threads > MAX_NUMBER_OF_THREADS) {
        number_of_running_threads = MAX_NUMBER_OF_THREADS;
    }

    int dk = MAX_NUMBER_OF_THREADS / number_of_running_threads;
    tabuleiros = malloc(sizeof(int *) * number_of_running_threads);
    for (int i = 0; i < number_of_running_threads; i++) {
        tabuleiros[i] = tabuleiro_alloc();
        running[i] = -1;
        pthread_create(&threads[i], NULL, async_try, &dk);
    }

    while (
        path_not_finded_or_tasks_are_running()
    ) { /* wait */ }

    for (int i = 0; i < number_of_running_threads; i++) {
        pthread_cancel(threads[i]);
    }
}

int main(void) {
    printf("x0: ");
    scanf("%d", &x0);
    printf("y0: ");
    scanf("%d", &y0);

    if (y0 < 0 || y0 >= H_SIZE || x0 < 0 || x0 >= H_SIZE) {
        printf("valores de coordenadas devem ser entre 0 e 7\n");
        return 1;
    }

    run_threads();

    int index = 0;
    for (; index < number_of_running_threads; index++) {
        if (running[index] == 1) break;
    }

    if (index >= number_of_running_threads) {
        printf("no path\n");
        return 0;
    }

    int *tabuleiro = tabuleiros[index];
    for (int y = 0; y < H_SIZE; y++) {
        printf("%2d | ", y+1);
        for (int x = 0; x < H_SIZE; x++) {
            printf("%02d ", tabuleiro_get(tabuleiro, x, y));
        }

        printf("\n");
    }

    printf("   .");
    for (int x = 0; x < H_SIZE; x++) {
        for (int x = 0; x < 3; x++) {
            printf("-");
        }
    }

    printf("\n");
    printf("    ");
    for (int x = 0; x < H_SIZE; x++) {
        printf("%3c", 'a'+x);
    }

    printf("\n");
    return 0;
}