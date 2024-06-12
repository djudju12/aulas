#include <stdio.h>

int tmult_ok_asm(long x, long y, long* dest) {
    long p = x*y;
    *dest = p;
    return p > 0;
}

int umult_ok_asm(unsigned long x, unsigned long y, unsigned long *dest) {
    unsigned long p = x*y;
    *dest = p;
    return p > 0;
}

int tmult_ok2(long x, long y, long* dest) {
    // int result;
    // *dest = x*y;
    // asm (
    //     "setae %%bl         # set low-order byte \n\t"
    //     "movzbl %%bl,%[val] # zero extend to be result"
    //     : [val] "=r" (result)   /* output     */
    //     :                       /* input      */
    //     : "%bl"                 /* overwrites */
    // );

    unsigned char bresult;
    asm(
        "imulq %[y],%[x]\n\t"
        "movq %[x],%[p]\n\t"
        "setae %[b]\n\t"
        : [p] "=m" (*dest), [b] "=r" (bresult)
        : [x] "r" (x), [y] "r" (y)
    );

    return (int) bresult;
}

// Multiply two 64-bit numbers to get 128-bit result,
void umult_full(unsigned long x, unsigned long y, unsigned long *dest) {
    asm(
        "movq %[x],%%rax\n\t"
        "mulq %[y]\n\t"
        "movq %%rax,%[p0]\n\t"
        "movq %%rdx,%[p1]\n\t"
        : [p0] "=m" (dest[0]), [p1] "=m" (dest[1])
        : [x] "r" (x), [y] "r" (y)
        : "%rax", "%rdx"
    );
}

int main(void) {
    long dest;
    printf("%ld %d", dest, tmult_ok2(100, 100, &dest));
}