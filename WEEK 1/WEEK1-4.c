#include<stdio.h>
void sort(int a[], int n){
    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-i-1; j++){
            if(a[j]>a[j+1]){
                int temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
    printf("Second largest element: %d", a[n-2]);
}

int main(){
    int arr[] = {5,6,3,1,7};
    int n = sizeof(arr)/sizeof(arr[0]);
    sort(arr, n);
    return 0;
}
