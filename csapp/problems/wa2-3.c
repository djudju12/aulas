#include <stdio.h>

int main(void) {
    /* WARNING: This code is buggy */
    /* Shift 1 over by 8*sizeof(long) - 1 */
    printf("%d\n", 1L << (sizeof(long)<<3) - 1);
}
