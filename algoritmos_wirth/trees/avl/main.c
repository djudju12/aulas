#include <stdio.h>
#include <assert.h>
#include<stdlib.h>
#include <stdbool.h>

typedef struct Node Node;

struct Node {
    int key;
    int cnt;
    int bal;
    Node *l, *r;
};

Node* new_node(int key) {
    Node *n = malloc(sizeof(Node));
    n->l = NULL;
    n->r = NULL;
    n->bal = 0;
    n->cnt = 1;
    n->key = key;
    return n;
}

void search(Node **root, int x, bool *h) {
    *h = false;

    Node *n = *root;
    if (n == NULL) {
        *root = n = new_node(x);
        *h = true;
    } else if (x < n->key) {
        search(&n->l, x, h);
        if (!(*h)) return;

        if (n->bal == 1) {
            n->bal = 0;
            *h = false;
        } else if (n->bal == 0) {
            n->bal = -1;
        } else if (n->bal == -1) {
            /* rebalanceamento */
            Node *n1 = n->l;
            if (n1->bal == -1) {
                /* rotacao simples LL */
                n->l = n1->r;
                n1->r = *root;
                n->bal = 0;
                *root = n = n1;
            } else {
                /* rotacao dupla LR */
                Node *n2 = n1->r;
                n1->r = n2->l;
                n2->l = n1;
                n->l = n2->r;
                n2->r = n;

                if (n2->bal == -1) {
                    n->bal = 1;
                } else {
                    n->bal = 0;
                }

                if (n2->bal == 1) {
                    n1->bal = -1;
                } else {
                    n1->bal = 0;
                }
                *root = n = n2;
            }
            n->bal = 0;
            *h = false;
        }
    } else if (x > n->key) {
        search(&n->r, x, h);
        if (!(*h)) return;

        if (n->bal == -1) {
            n->bal = 0;
            *h = false;
        } else if (n->bal == 0) {
            n->bal = 1;
        } else if (n->bal == 1) {
            Node *n1 = n->r;
            if (n1->bal == 1) {
                /* rotacao simples RR */
                n->r = n1->l;
                n1->l = *root;
                n->bal = 0;
                *root = n = n1;
            } else if (n1->bal == -1) {
                /* rotacao dupla RL */
                Node *n2 = n1->l;
                n1->l = n2->r;
                n2->r = n1;
                n->r = n2->l;
                n2->l = *root;
                if (n2->bal == 1) {
                    n->bal = -1;
                } else {
                    n->bal = 0;
                }

                if (n2->bal == -1) {
                    n1->bal = 1;
                } else {
                    n1->bal = 0;
                }
                *root = n = n2;
            }
            n->bal = 0;
            *h = false;
        }
    } else {
        n->cnt++;
    }
}

void tree_dump(Node *root, int level) {
    if (root == NULL) return;
    printf("%*s[%d] %d => %d\n",
            level*2, "", level, root->key, root->bal);
    tree_dump(root->l, level + 1);
    tree_dump(root->r, level + 1);
}

void free_tree(Node *root) {
    if (root == NULL) return;
    free_tree(root->l);
    free_tree(root->r);
    free(root);
}

int main(void) {
    int entries[] = { 4, 5, 7, 2, 1, 3, 6 };
    Node *root = NULL;
    bool h = false;
    for (int i = 0; i < 7; i++) {
        search(&root, entries[i], &h);
    }

    tree_dump(root, 0);
    free_tree(root);
    return 0;
}