#include <stdio.h>

#define DIM1 5
#define DIM2 3

void search_and_copy(char m1[DIM1][DIM1], char m2[DIM2][DIM2], char m3[DIM1][DIM1]);
void print_matrix(char m[DIM1][DIM1], int n);

int main(void) {
    /*char m1[DIM1][DIM1] = {
        {'*', '#', '*', '*', '*'},
        {'#', '#', '#', '*', '*'},
        {'*', '#', '*', '#', '*'},
        {'*', '*', '#', '#', '#'},
        {'*', '*', '*', '#', '*'}
    };

    char m2[DIM2][DIM2] = {
        {'*', '#', '*'},
        {'#', '#', '#'},
        {'*', '#', '*'}
    };*/
    char m1[DIM1][DIM1];
    printf("Please input matrix 1 with size %dx%d\n", DIM1, DIM1);
    for (int i = 0; i < DIM1; i++) {
        for (int j = 0; j < DIM1; j++) {
            scanf(" %c", &m1[i][j]); 
        }
    }
    char m2[DIM2][DIM2];
    printf("Please input matrix 2 with size %dx%d\n", DIM2, DIM2);
    for (int i = 0; i < DIM2; i++) {
        for (int j = 0; j < DIM2; j++) {
            scanf(" %c", &m2[i][j]); 
        }
    }
    char m3[DIM1][DIM1];
    for (int i = 0; i < DIM1; i++)
        for (int j = 0; j < DIM1; j++)
            m3[i][j] = ' ';
    search_and_copy(m1, m2, m3);
    print_matrix(m3, DIM1);
    return 0;
}

void search_and_copy(char m1[DIM1][DIM1], char m2[DIM2][DIM2], char m3[DIM1][DIM1]) {
    for (int row = 0; row < DIM1 - DIM2 + 1; row++) {
        for (int col = 0; col < DIM1 - DIM2 + 1; col++) {
            int flag = 1;
            for (int i = 0; i < DIM2 && flag; i++) {
                for (int j = 0; j < DIM2; j++) {
                    if (m1[row + i][col + j] != m2[i][j]) {
                        flag = 0;
                        break;
                    }
                }
            }
            if (flag) {
                for (int i = 0; i < DIM2; i++) {
                    for (int j = 0; j < DIM2; j++) {
                        m3[row + i][col + j] = m2[i][j];
                    }
                }
            }
        }
    }
}

void print_matrix(char m[DIM1][DIM1], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%c", m[i][j]);
        printf("\n");
    }
}
