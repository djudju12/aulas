#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Item Item;

struct Item {
    int value;
    Item *next;
};

typedef struct {
    Item *first;
    Item *last;
} Vec;

typedef struct Node Node;

#define MAX_LINES 256
#define MAX_KEY   256

struct Node {
    char key[MAX_KEY];
    Vec *lines;
    Node *left, *right;
};

Node *new_node(char *key) {
    Node *node = malloc(sizeof(Node));
    assert(node != NULL && "buy more ram!!");
    strncpy(node->key, key, MAX_KEY);
    node->left  = NULL;
    node->right = NULL;
    node->lines = malloc(sizeof(Vec));
    assert(node->lines != NULL && "buy more ram!!");
    return node;
}

void search_and_insert(Node **root, char *key, int line) {
    Node *n;
    if (*root == NULL) {
        n = new_node(key);
        Item *first_item = malloc(sizeof(Item));
        assert(first_item != NULL && "buy more ram!!");
        first_item->value = line;
        first_item->next = NULL;
        n->lines->first = first_item;
        n->lines->last = first_item;
        *root = n;
    } else {
        n = *root;
        int diff = strncmp(key, n->key, MAX_KEY);
        if (diff < 0) {
            search_and_insert(&n->left, key, line);
        } else if (diff > 0) {
            search_and_insert(&n->right, key, line);
        } else {
            Item *new_item = malloc(sizeof(Item));
            assert(new_item != NULL && "buy more ram!!");
            new_item->value = line;
            new_item->next = NULL;
            n->lines->last->next = new_item;
            n->lines->last = new_item;
        }
    }
}

void print_tree(Node *root, FILE *out, int level) {
    if (root == NULL) return;
    printf("%*c%s\n", level*2, ' ', root->key);
    print_tree(root->left, out, level + 1);
    print_tree(root->right, out, level + 1);
}

void tree_dump(Node *root, FILE *out) {
    if (root != NULL) {
        tree_dump(root->left, out);
        fprintf(out, "%s ", root->key);
        Vec *line_numbers = root->lines;
        Item *curent_item = line_numbers->first;
        while (curent_item != NULL) {
            fprintf(out, "%d ", curent_item->value);
            curent_item = curent_item->next;
        }

        fprintf(out, "\n");
        tree_dump(root->right, out);
    }
}

void free_tree(Node *root) {
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main(int argc, char **argv) {
    const char *file_path = "/home/kopp/fontes/pessoal/1brc/measurements1kkk.txt";
    FILE *file = fopen(file_path, "r");

    assert(file != NULL && "cannot open the file");

    Node *root = NULL;
    char chr, buff[256];
    int cnt, line = 1;
    while ((chr = fgetc(file)) != EOF) {
        while (isspace(chr)) {
            if (chr == '\n') line++;
            chr = fgetc(file);
        }

        cnt = 0;
        if (isalpha(chr)) {
            while(chr != EOF && !isspace(chr) && isalpha(chr)) {
                buff[cnt++] = tolower(chr);
                chr = fgetc(file);
            }

            buff[cnt] = '\0';

            search_and_insert(&root, buff, line);
        } else {
            while(chr != EOF && !isspace(chr)) chr = fgetc(file);
            if (chr == '\n') line++;
        }
    }

    print_tree(root, stdout, 0);
    free_tree(root);
    fclose(file);
    return 0;
}