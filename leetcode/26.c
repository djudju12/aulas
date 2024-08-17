#include <stdio.h>

int nums[] = {0,0,1,1,1,2,2,3,3,4};

int remove_duplicates(int *nums, int nums_size);

int main(void) {
    int N = sizeof(nums)/sizeof(nums[0]);
    int k = remove_duplicates(nums, N);
    printf("k = %d\n", k);
    for (int i = 0; i < N; i++) {
        printf("%d ", nums[i]);
    }

    printf("\n");
    return 0;
}

int remove_duplicates(int *nums, int nums_size) {
    if (nums_size == 0) {
        return 0;
    }

    int k, i, last = nums[0];
    for (k = i = 1; i < nums_size; i++) {
        if (nums[i] > last) {
            last = nums[i];
            nums[k++] = last;
        }
    }

    return k;
}
