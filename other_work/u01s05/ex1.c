#include <stdio.h>

#define DIM 8

int main(void) {
    int arr[DIM] = {0};
    for (int i = 0; i < DIM; i++) {
        scanf("%d", &arr[i]);
    }
    int elem_count = 0;
    for (int i = 0; i < DIM; i++) {
        if (arr[i] != 0) {
            arr[elem_count] = arr[i];
            elem_count++;
       }
    }
    for (int i = 0; i < elem_count; i++) {
        printf("%d ", arr[i]);
    } printf("\n");
    return 0;
}