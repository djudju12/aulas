#include <stdio.h>
#include <stdlib.h>

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

    content = (char *) malloc(sizeof(char)*file_size);
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