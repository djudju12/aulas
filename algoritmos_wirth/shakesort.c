#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LEN 50

int arr[MAX_LEN];

int randomInRange(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void make_array(int *arr, int len) {
    for (size_t i = 0; i < len; i ++) {
        arr[i] = randomInRange(0, 1000);
    }
}

void print_array(int *arr, int len) {
    printf("[");
    for (size_t i = 0; i < len; i ++) {
        if (i > 0) {
            printf(", ");
        }
        printf("%d", arr[i]);
    }
    printf("]\n");
}

void shake_sort(int *arr, int len) {
    int r, k, l;
    r = k = len-1;
    l = 0;

    do {
        for (size_t i = r; i > l; i--) {
            if (arr[i-1] > arr[i]) {
                int temp = arr[i-1];
                arr[i-1] = arr[i];
                arr[i] = temp;
                k = i;
            }
        }

        l = k;

        for (size_t i = l; i < r; i++) {
            if (arr[i+1] < arr[i]) {
                int temp = arr[i+1];
                arr[i+1] = arr[i];
                arr[i] = temp;
                k = i;
            }
        }
        r = k;

    } while (l < r);
}

void bubble_sort(int *arr, int len) {
    for (size_t i = 1; i < len; i++) {
        for (size_t j = len-1; j >= i; j--) {
            if (arr[j-1] > arr[j]) {
                int temp = arr[j-1];
                arr[j-1] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main(void) {
    srand(time(NULL));
    make_array(arr, MAX_LEN);
    print_array(arr, MAX_LEN);
    shake_sort(arr, MAX_LEN);
    print_array(arr, MAX_LEN);
    return 0;
}
