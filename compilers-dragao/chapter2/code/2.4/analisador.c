#include <stdio.h>
#include <stdlib.h>

char * read_all_file(char *file_path, int *ferr);
char *lookahead;
int main(int argc, char **argv)
{
    char *program_name = argv[0];
    char *file_path;
    int ferr;

    if (argc < 2) {
        printf("%s usage: %s <file_path>\n", program_name, program_name);
        return 1;
    }

    program_name = argv[0];
    file_path = argv[1];

    lookahead = read_all_file(file_path, &ferr);
    if (!lookahead) {
        printf("could not read the file %s. ferr: %d\n", file_path, ferr);
        return 1;
    }

    /*
    S ->  + S S
        | - S S
        | a
    */
    void analyze(void);
    analyze();
    printf("\nvalid syntax\n");
    return 0;
}

void analyze(void)
{
    void stmt(void);
    stmt();
}
void match(char t);

void stmt(void)
{
    /*
    S ->  S(S)S
         | E
    */
    void optstmt(void);
    switch (*lookahead) {
        case '(':
            match('(');optstmt();match(')');optstmt();
            break;
        case ')':
            break;
        default:
            printf("\nsyntax error\n");
            exit(1);
    }
}

void optstmt(void)
{
    if (*lookahead == '(')
        stmt();
}

void stmt1(void)
{
    /*
    S ->  + S S
        | - S S
        | a
    */
    switch (*lookahead) {
        case 'a':
            match('a');
            break;
        case '+':
            match('+'); stmt(); stmt();
            break;
        case '-':
            match('+'); stmt(); stmt();
            break;
        default:
            printf("\nsyntax error\n");
            exit(1);
    }
}

void match(char t)
{
    if (*lookahead == t) {
        lookahead++;
        printf("%c", t);
    } else {
        printf("\nsyntax error\n");
        exit(1);
    }
}

char * read_all_file(char *file_path, int *ferr)
{
    FILE *f;
    char *content;
    long file_size;
    size_t ret;

    *ferr = 0;
    f = fopen(file_path, "r");
    if (!f) goto ERROR;

    fseek(f, 0, SEEK_END);
    file_size = ftell(f);
    rewind(f);

    content = malloc(sizeof(char)*file_size);
    if (!content) goto ERROR;

    ret = fread(content, sizeof(char), file_size, f);
    if (ret != file_size)
        goto ERROR;

    return content;

ERROR:
    if (f) {
        *ferr = ferror(f);
        free(f);
    }

    if (content) free(content);
    return NULL;
}