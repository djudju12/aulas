#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *gets(char *s) {
    int c;
    char *dest = s;
    while ((c = getchar()) != '\n' && c != EOF) {
        *dest++ = c;
    }

    if (c == EOF && dest == s) {
        return NULL;
    }

    *dest++ = '\0';
    return s;
}

char *get_line(void) {
    char buf[4];
    char *result;
    gets(buf);
    result = malloc(strlen(buf));
    strcpy(result, buf);
    return result;
}

// [00 00 00 00 00 40 00 39]
// [30 31 32 33 34 || || ||}
int main(void) {
    char *s = get_line();
    printf("%s\n", s);
    return 0;
}
