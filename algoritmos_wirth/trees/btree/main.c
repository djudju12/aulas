#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 2

typedef struct Page Page;

typedef struct {
    int key;
    int cnt;
    Page *p;
} Item;

struct Page {
    int m;
    Item items[2*N];
    Page *p0;
};


void print_tree(Page *root, int level) {
    if (root == NULL) return;

    if (root->p0) {
        printf("%*s[%d] p0\n", level*2, "", level);
        print_tree(root->p0, level + 1);
    }

    for (int i = 0; i < root->m; ++i) {
        printf("%*s[%d] %d\n", level*2, "", level, root->items[i].key);
        print_tree(root->items[i].p, level + 1);
    }
}

Page *new_page() {
    Page *p = malloc(sizeof(Page));
    p->p0 = NULL;
    p->m = 0;
    return p;
}

void _search(int x, Page *a, bool *h, Item *v) {
    if (a == NULL) {
        *h = true;
        v->cnt = 1;
        v->key = x;
        v->p = NULL;
        return;
    }
    /* linear array search */
    int k = 0;
    while (k < a->m && x > a->items[k].key) k++;

    bool found = a->items[k].key == x;
    if (found) {
        a->items[k].cnt++;
        *h = false;
    } else {
        /* item is not in this page */
        Page *q = (k == 0) ? a->p0 : a->items[k - 1].p;

        _search(x, q, h, v);
        if (!(*h)) return;

        Item u = *v;
        if (a->m < 2*N) {
            /* inserts new item in position k */
            for (int i = a->m; i > k; --i) {
                a->items[i] = a->items[i - 1];
            }

            a->items[k] = u;
            a->m++;
            *h = false;
        } else {
            /* splits */
            Page *b = new_page();

            if (k < N) {
                /* k is in the left */
                *v = a->items[N - 1]; // middle of the array merged
                for (int i = k; i < N - 1; ++i) {
                    a->items[i + 1] = a->items[i];
                }

                a->items[k] = u;

                for (int i = N; i < 2*N; ++i) {
                    b->items[i - N] = a->items[i];
                }

            } else if (k > N) {
                /* k is in the right */
                *v = a->items[N];

                int j = 0;
                for (int i = N + 1; i < k; ++i) {
                    b->items[j++] = a->items[i];
                }

                b->items[j++] = u;

                for (int i = k + 1; i < a->m; ++i) {
                    b->items[j++] = a->items[i];
                }

            } else {
                /* k is in the middle */
                for (int i = N; i < a->m; ++i) {
                    b->items[i - N] = a->items[i];
                }
            }

            a->m = b->m = N;
            b->p0 = v->p;
            v->p = b;
        }
    }
}

Page *new() {
    Page *p = malloc(sizeof(Page));
    p->m = 0;
    return p;
}

int main(void) {
    Page *root = new();
    Page *q = NULL;
    int values[] = { 20, 40, 10, 30, 15, 35, 7, 26, 18, 22, 5, 42, 13, 46, 27, 8, 32 , 38, 24, 45, 25
    };
    bool h = false;
    Item u = { .p = NULL };

    for (int i = 0; i < (sizeof(values)/(sizeof(values)[0])); ++i) {
        _search(values[i], root, &h, &u);
        if (h) {
            q = root;
            root = new();
            root->m = 1;
            root->p0 = q;
            root->items[0] = u;
        }
    }

    print_tree(root, 0);

    return 0;
}