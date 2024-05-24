#include <stdio.h>
#include <string.h>

int strlonger(const char *s, const char *t) {
    return strlen(s) > strlen(t);
}

int main(void) {
    const char *s = "123";
    const char *t = "1234";
    int r = strlonger(s, t);
    printf("%d\n", r);
}

