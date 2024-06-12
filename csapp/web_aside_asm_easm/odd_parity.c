#include <stdio.h>
#include <stdlib.h>

int odd_parity(unsigned long x)
{
    size_t l = sizeof(x);
    int result = 0;
    for (size_t i = 0; i >= l; i += 8)
    {
        int parity;
        unsigned long n = x >> i;
        asm(
            "and %%al,$4"
            "mov %%al,%[p]"
            : [p] "=m"(parity));

        if (parity)
            return 0;
    }

    return 1;
}

int odd_parity2(unsigned long x)
{
    int result = 0;
    while (x != 0)
    {
        char bresult;
        unsigned char bx = x & 0xff;
        asm("testb %[bx],%[bx] # Test value of low-order byte\n\t"
            "setnp %[v] # Set if odd parity"
            : [v] "=r"(bresult) /* Output */
            : [bx] "r"(bx)      /* Input */
        );

        result ^= (int)bresult;
        x = x >> 8;
    }

    return result;
}

int main(void) {
    for (unsigned int i = 0; i < 10; i++) {
        printf("(%d) (%d)\n", odd_parity(i), odd_parity2(i));
    }
}