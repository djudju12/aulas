#include <stdio.h>
//
//#define M 3
//#define N 3

//int ns1[M+N] = {4,5,6,0,0,0};
//int ns2[N]   = {1,2,3};

#define M 5
#define N 2

int ns1[M+N] = {-1,0,5,5,8,0,0};
int ns2[N]   = {2,5};

void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n) {
    if (m == 0) {
        for (int i = 0; i < n; i++) nums1[i] = nums2[i];
        return;
    }

    for (int i = 0; i < n; i++, m++) {
        int k = nums2[i];
        int r = m - 1;
        int l = 0;
        int mid;
        while (l <= r) {
            mid = (l + r)/2;

            int diff = k - nums1[mid];
            if (diff == 0) break;

            if (diff > 0) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }

        if (mid < m && k > nums1[mid]) mid += 1;

        for (int j = m; j > mid; j--) {
            nums1[j] = nums1[j - 1];
        }

        nums1[mid] = k;
    }
}

int main(void) {
    for (int i = 0; i < (M + N); i++) printf("%d ", ns1[i]);
    printf("\n");

    merge(ns1, N + M, M, ns2, N, N);

    for (int i = 0; i < (M + N); i++) printf("%d ", ns1[i]);
    printf("\n");

    return 0;
}
