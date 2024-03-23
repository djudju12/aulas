#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

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

bool is_sorted(int *arr, int len) {
    for (size_t i = 1; i < len; i++) {
        if (arr[i-1] > arr[i]) {
            return false;
        }
    }

    return true;
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

void insertion_sort(int *arr, int len) {
    int temp, j;
    for (size_t i = 1; i < len; i++) {
        temp = arr[i];
        j = i;
        while (j > 0 && arr[j - 1] > temp) {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = temp;
    }
}

void insertion_sort_binary(int *arr, int len) {
    int temp, j;
    int l, m, r;

    for (size_t i = 1; i < len; i++) {
        temp = arr[i];
        l = 0; r = i;

        while (l < r) {
            m = (l+r) / 2;
            if (arr[m] <= temp) l = m+1;
            else r = m;
        }

        for (size_t j = i; j > r ; j--) {
            arr[j] = arr[j-1];
        }

        arr[r] = temp;
    }
}

void selection_sort(int *arr, int len) {
    int min, n, temp;

    n = 0;
    while (n < len) {
        min = n;
        for (size_t i = n+1; i < len; i++) {
            if (arr[i] < arr[min]) {
                min = i;
            }
        }

        temp = arr[n];
        arr[n] = arr[min];
        arr[min] = temp;
        n++;
    }

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

void shell_sort(int *arr, int len) {
    const int t = 4;
    int incrementos[] = {9, 5, 3, 1};
    int k, j, temp;

    for (size_t m = 0; m < t; m++) {
        k = incrementos[m];
        for (size_t i = k; i < len; i++) {
            temp = arr[i];
            j = i - k;
            while (j >= 0 && temp < arr[j]) {
                arr[j + k] = arr[j];
                j -= k;
            }
            arr[j + k] = temp;
        }
    }
}

void _sift(int *arr, int l, int r) {
    int i, j, temp;

    i = l; j = 2*l + 1;
    temp = arr[l];
    if (j < r && arr[j+1] > arr[j]) j++;
    while (j <= r && arr[j] > temp) {
        arr[i] = arr[j];
        arr[j] = temp;
        i = j; j = (2*j) + 1;
        if (j < r && arr[j+1] > arr[j]) j++;
    }
}

void _heapfy(int *arr, int len) {
    int l = len / 2;

    while (l > 0) {
        l--;
        _sift(arr, l, len);
    }
}

void heap_sort(int *arr, int len) {
    int r, temp;
    r = len-1;

    _heapfy(arr, r);
    while (r > 0) {
        temp = arr[0];
        arr[0] = arr[r];
        arr[r] = temp;
        _sift(arr, 0, --r);
    }
}

void _sort(int *arr, int l, int r) {
    int temp, pivot = arr[r];
    int i = l, j = r-1;
    do {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i <= j) {
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    } while (i <= j);
    arr[r] = arr[i];
    arr[i] = pivot;
    if (l < j) _sort(arr, l, j);
    if (r > i) _sort(arr, i, r);
}

void quick_sort(int *arr, int len) {
    _sort(arr, 0, len-1);
}

int main(void) {
    // srand(time(NULL));

    // // int a[] = {44, 55, 12, 42, 94, 6, 18, 67};
    // // int len = 8;

    // make_array(arr, 20);
    // print_array(arr, 20);
    // _partition(arr, 0, 19);
    // print_array(arr, 20);
    // return 0;
    /////

    make_array(arr, MAX_LEN);
    quick_sort(arr, MAX_LEN);

    if (is_sorted(arr, MAX_LEN)) {
        printf("ITS SORTED\n");
        return 0;
    }

    printf("ITS NOT SORTED\n");
    return 1;
}
