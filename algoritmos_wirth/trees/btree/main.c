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
    int m ;
    Item items[2*N];
    Page *p0;
};

void search(int x, Page **p) {
    void _search(int x, Page *a, bool *h, Item **v);
    bool h = false;
    Item *item = NULL;

    if (*p == NULL) {
        *p = malloc(sizeof(Page));
        (*p)->p0 = NULL;
        (*p)->m = 1;
        (*p)->items[0].cnt = 1;
        (*p)->items[0].key = x;
        (*p)->items[0].p = NULL;
    } else {
        _search(x, *p, &h, &item);
    }
}
void _search(int x, Page *a, bool *h, Item **v) {
    if (a == NULL) {
        assert(*v == NULL);
        *h = true;
        *v = malloc(sizeof(Item));
        (*v)->cnt = 1;
        (*v)->key = x;
        (*v)->p = NULL;
    } else {
        /* binary array search */
        int l, r, k;
        l = 0, r = a->m - 1;
        do {
            k = (l+r) / 2;
            if (x <= a->items[k].key) r = k-1;
            if (x >= a->items[k].key) l = k+1;
        } while (r >= l);

        if (l-r > 1) { // tem um erro aq
            /* found */
            a->items[k].cnt++;
            *h = false;
        } else {
            /* item is not in this page */
            Page *q = (r == -1) ? a->p0 : a->items[r].p;
            _search(x, q, h, v);
            if (!(*h)) return;
            Item *u = *v;
            /* inserts new item */
            if (a->m < 2*N) {
                for (int i = a->m; i > r+1; --i) {
                    a->items[i] = a->items[i - 1];
                }

                assert(v != NULL);
                a->items[r+1] = *u;
                a->m++;
                *h = false;
            } else {
                /* splits */
                Page *b = malloc(sizeof(Page));
                b->p0 = a->p0;
                b->m = 0;

                Item temp = *u;
                if (r < N) {
                    *v = &a->items[N]; // check
                    for (int i = N; i > r+1; --i) {
                        a->items[i] = a->items[i - 1];
                    }
                    a->items[r] = temp;
                } else {
                    r = r - N;
                    *v = &a->items[N]; // check
                    for (int i = 0; i < r; ++i) {
                        b->items[i] = a->items[i+N+1];
                    }
                    b->items[r] = temp;
                    for (int i = r+1; i < N; ++i) {
                        b->items[i] = a->items[i+N];
                    }
                    a->m = N;
                    b->m = N;
                    b->p0 = u->p;
                    u->p = b;
                }
            }

        }
    }
}

int main(void) {
    Page *p = NULL;
    search(20, &p);
    search(40, &p);
    search(10, &p);
    search(30, &p);
    search(15, &p);
    return 0;
}