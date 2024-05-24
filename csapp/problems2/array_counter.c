#include <stdio.h>

float sum_elements(float a[], unsigned len) {
    float result = 0;

    int i;
    for (i = 0; i < len; i++) {
        result += a[i];
    }

    return result;
}

int main(void) {
    float a[1] = {1.0};
    float r = sum_elements(a, 0);
    printf("%f\n", r);
    return 0;
}
