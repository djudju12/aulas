#include <stdio.h>

int nums[] = {0,0,1,1,1,1,2,3,3};

int remove_duplicates(int *nums, int numsSize);

int main(void) {
    int N = sizeof(nums)/sizeof(nums[0]);
    for (int i = 0; i < N; i++) printf("%d ", nums[i]);
    printf("\n");

    int k = remove_duplicates(nums, N);
    printf("k = %d\n", k);
    for (int i = 0; i < N; i++) printf("%d ", nums[i]);
    printf("\n");

    return 0;
}

int remove_duplicates(int *nums, int numsSize) {
    if (numsSize == 0) {
        return 0;
    }

    int k, c, i, last = nums[0];
    for (k = i = c = 1; i < numsSize; i++) {
        if (nums[i] == last && c == 1) {
            c += 1;
            nums[k++] = last;
        } else if (nums[i] > last) {
            c = 1;
            last = nums[i];
            nums[k++] = last;
        }
    }

    return k;
}
