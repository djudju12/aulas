#include <stdio.h>
#include "utils.h"
#include <ctype.h>


void match(char);
void expr(void);
void rest(void);
void term(void);

char *lookahead;

void term(void)
{
    if (isdigit(*lookahead)) {
        char t = *lookahead;
        match(*lookahead);
        printf("%c", t);
    } else {
        printf("\nsyntax error\n");
        exit(1);
    }
}

void rest(void)
{
    while( 1 ) {
        if (*lookahead == '+') {
            match('+'); term(); printf("+"); continue;
        } else if (*lookahead == '-') {
            match('-'); term(); printf("-"); continue;
        } else {
            break;
        }
    }
}

void expr(void)
{
    term(); rest();
}

void match(char t)
{
    if (*lookahead == t) {
        lookahead++;
    } else {
        printf("\nsyntax error\n");
        exit(1);
    }
}

int main(void)
{
    int ferror;
    lookahead = read_all_file("input.txt", &ferror);
    if (!lookahead || ferror != 0) {
        printf("error opening the file\n");
        return 1;
    }

    expr();
    return 0;
}