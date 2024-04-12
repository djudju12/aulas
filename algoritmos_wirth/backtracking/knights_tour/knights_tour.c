#include <stdio.h>

/*
    Dado um tabuleiro nxn, com n² campos. Um cavalo - que se move segundos as
    regras do xadrez - é colocado no campo com as coordenadas inciais x0 e y0.
    O problema a ser resolvido consistem em se encontrar uma forma de cobrir
    todo o tabuleiro, se é que existe de fato uma maneira de faze-lo, isto é
    de calcular um percurso n²-1 movimentos, tal que todas as células do tabu_
    leiro sejam percorridas exatamente uma vez.
*/

#define H_SIZE 8
int tabuleiro[H_SIZE][H_SIZE] = {0};

int dx[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
int dy[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

int isAceitavel(int x1, int y1) {
    return (y1 >= 0)
        && (y1 < H_SIZE)
        && (x1 >= 0)
        && (x1 < H_SIZE)
        && (tabuleiro[y1][x1] == 0);
}

long int total_tries = 0;
int try(int i, int x, int y) {
    total_tries++;
    int q1 = 0;
    for (int k = 0; k < H_SIZE && q1 != 1; k++) {
        int y1 = y + dy[k];
        int x1 = x + dx[k];
        if (isAceitavel(x1, y1)) {
            tabuleiro[y1][x1] = i;
            if (i < H_SIZE*H_SIZE) {
                q1 = try(i+1, x1, y1);
                if (q1 == 0) {
                    tabuleiro[y1][x1] = 0;
                }
            } else {
                q1 = 1;
            }
        }
    }

    return q1;
}


int main(void) {
    int x0, y0;
    printf("posicao x inicial do cavalo: \n");
    scanf("%d", &x0);
    printf("posicao y inicial do cavalo: \n");
    scanf("%d", &y0);
    printf("\n");

    if (y0 < 0 || y0 >= H_SIZE || x0 < 0 || x0 >= H_SIZE) {
        printf("valores de coordenadas devem ser entre 0 e 7\n");
        return 1;
    }

    tabuleiro[y0][x0] = 1;
    int q = try(2, x0, y0);
    if (q == 0) {
        printf("no path\n");
    }

    for (int y = 0; y < H_SIZE; y++) {
        printf("%2d | ", y+1);
        for (int x = 0; x < H_SIZE; x++) {
            printf("%02d ", tabuleiro[y][x]);
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
    printf("\n");
    printf("total de saltos: %ld\n", total_tries);
    return 0;
}