#include <stdio.h>

int misdigit(char c) {
    return c >= '0' && c <= '9';
}

int str2dec(const char *str) {
    char c = *str;
    int num = 0;
    while (c != '\0' && misdigit(c)) {
        num = (num * 10) + (c - '0');
        c = *(++str);
    }

    return num;
}

char tohex(int n) {
    if (n < 10) {
        return n + '0';
    } else {
        return n - 10 + 'A';
    }
}

int main(int argc, char **argv) {
    const char *program_name = argv[0];
    if (argc < 2) {
        printf("usage: \n\t%s <decimal-number>\n", program_name);
        return 1;
    }

    const char *dec = argv[1];
    int num = str2dec(dec);


    char hex[12] = {'0', 'x'};
    int i = 2;
    while (num > 0) {
        hex[i++] = tohex(num % 16);
        num /= 16;
    }

    hex[i] = '\0';
    char t;
    for (int j = 0; j < (i - 2) / 2; ++j) {
        t = hex[j + 2];
        hex[j + 2] = hex[i - j - 1];
        hex[i - j - 1] = t;
    }

    printf("%s\n", hex);
    return 0;
}