#include <stdio.h>

void rowSum(int a[][4], int r, int c) {
    int rs[r];
    for (int i = 0; i < r; i++) {
        int rsum = 0;
        for (int j = 0; j < c; j++)
            rsum += a[i][j];
        rs[i] = rsum;
    }
    printf("Row Sum:\n");
    for (int i = 0; i < r; i++)
        printf("%d ", rs[i]);
    printf("\n");
}

void colSum(int a[][4], int r, int c) {
    int cs[c];
    for (int j = 0; j < c; j++) {
        int csum = 0;
        for (int i = 0; i < r; i++)
            csum += a[i][j];
        cs[j] = csum;
    }
    printf("Column Sum:\n");
    for (int j = 0; j < c; j++)
        printf("%d ", cs[j]);
    printf("\n");
}

int main() {
    int a[4][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {8, 7, 6, 5},
        {4, 3, 2, 1}
    };

    rowSum(a, 4, 4);
    colSum(a, 4, 4);

    return 0;
}
