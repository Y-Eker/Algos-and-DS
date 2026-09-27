#include <stdio.h>

#define NUM_OF_RANGES 10
#define SIZE_OF_RANGES 10

int main(void) {
    int counter[NUM_OF_RANGES] = {0};
    while (1) {
        int n;
        scanf("%d", &n);
        if (n < 0 || n > 99) break;
        counter[n / SIZE_OF_RANGES]++;
    }
    for (int i = 0; i < NUM_OF_RANGES; i++) {
        printf("%2d - %2d ", i * SIZE_OF_RANGES, i * SIZE_OF_RANGES + SIZE_OF_RANGES - 1);
        for (int j = 0; j < counter[i]; j++)
            printf("#");
        printf("\n");
    }
    return 0;
}
