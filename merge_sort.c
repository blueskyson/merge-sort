#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>
#define MAX 1000
#define HALF 512
int arr[MAX], left_sub[HALF], right_sub[HALF];
void merge_sort(int left, int right) {
    if(left < right) {
        int mid = (left + right)/2;
        merge_sort(left, mid);
        merge_sort(mid+1, right);
        int ind_l = 0, ind_r = 0, i;
        for(i=left; i<=mid; ++i,++ind_l) {
            left_sub[ind_l] = arr[i];
        }
        for(i = mid+1; i<=right; ++i,++ind_r) {
            right_sub[ind_r] = arr[i];
        }
        left_sub[ind_l] = right_sub[ind_r] = INT_MAX;
        int index = left;
        ind_l = ind_r = 0;
        while(index<=right){
            if(left_sub[ind_l] < right_sub[ind_r]) {
                arr[index] = left_sub[ind_l];
                ind_l++;
            }
            else {
                arr[index] = right_sub[ind_r];
                ind_r++;
            }
            index++;
        }
    }
}

int main() {
    int amount, max, i;
    printf("enter amount and max value:\n");
    scanf("%d %d",&amount,&max);
    if(amount > MAX) {
        printf("the amount of number must < %d\n", MAX);
        return 0;
    }
    srand(time(NULL));
    printf("orig order:");
    for(i=0; i<amount; ++i) {
        arr[i] = rand()%max+1;
        printf(" %d",arr[i]);
    }
    printf("\n\n");

    merge_sort(0,amount-1);
    printf("sorted order:");
    for(i=0; i<amount; ++i) {
        printf(" %d",arr[i]);
    }
    printf("\n");
    return 0;
}

