//Write a program in C to find the sum of the left diagonals of a matrix.
#include<stdio.h>
void diagonalSum(int a[][4], int n){
    int sum = 0;
    for(int i=0; i<n; i++)
        sum+=a[i][i];
    printf("Diagonal sum = %d", sum);
}

int main() {
    int a[4][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {8, 7, 6, 5},
        {4, 3, 2, 1}
    };
    diagonalSum(a, 4);
    return 0;
}

