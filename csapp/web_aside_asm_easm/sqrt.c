#include <stdio.h>

double sqrtd(double n) {
    double result;
    asm(
        "sqrtsd %[n],%[r]"
        : [r] "=x" (result)
        : [n] "x" (n)
    );
    return result;
}

int main(void) {
    printf("%lf\n", sqrtd(2.5));
}