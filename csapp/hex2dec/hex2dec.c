#include <stdio.h>

int mstrlen(const char *str) {
    int len = 0;
    const char *s = str;
    while (*s != '\0') {
        s++;
        len++;
    }

    return len;
}

char mupper(char c) {
    if (c >= 'A' && c <= 'F') {
        return c;
    } else {
        return 'A' + (c - 'a');
    }
}

char fromhex(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    } else {
        return (mupper(c) - 'A') + 10;
    }
}

int power(int b, int x) {
    int r = 1;
    for (int i = 0; i < x; i++) {
        r = b * r;
    }

    return r;
}

void usage(const char *program_name) {
    printf("usage: \n\t%s <hex-number>\n", program_name);
    printf("\thex-number = 0[xX][0-9A-F]+\n");
}

int main(int argc, char **argv) {
    const char *program_name = argv[0];
    if (argc < 2) {
        usage(program_name);
        return 1;
    }

    const char *hex = argv[1];
    int len = mstrlen(hex);
    if (len < 2) {
        usage(program_name);
        return 1;
    }

    if (hex[0] != '0' || (hex[1] != 'x' && hex[1] != 'X')) {
        usage(program_name);
        return 1;
    }

    int dec = 0;
    for (int i = 2; i < len; ++i) {
        dec += fromhex(hex[i])*power(16, len - i - 1 );
    }

    printf("%d\n", dec);
    return 0;
}