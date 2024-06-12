#include <stdio.h>

double dmin(double x, double y) {
    if(x < y) {
        return x;
    } else {
        return y;
    }
}

double dmin_asm(double x, double y) {
    double result;
    asm (
        "vminsd %[x],%[y],%[r]"
        : [r] "+x" (result)
        : [x] "x" (x), [y] "x" (y)
    );

    return result;
}

int main(void) {
    printf("%lf\n", dmin(10.5, 9.5));
    printf("%lf\n", dmin_asm(10.5, 9.5));
}