#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void sort(int arr[],int front,int end);
int main() {
    int n,max,i,j;
    printf("please input amounts of number and max value\n");
    scanf("%d %d",&n,&max);
    int arr[n];
    srand(time(NULL));
    printf("orig order:");
    for(i=0; i<n; i++) {
        arr[i]=rand()%max+1;
        printf("%3d ",arr[i]);
    }
    sort(arr,0,n-1);
    printf("\nnew order:");
    for(i=0; i<n; i++)
        printf("%3d ",arr[i]);
    printf("\n");
    return 0;
}

void sort(int arr[], int front, int end) {
    if(front<end) {
        int i, index=front, pivot=arr[end], tmp;
        for(i=front; i<end; i++) {
            if(arr[i]<pivot) {
                tmp=arr[i];         //swap
                arr[i]=arr[index];  //
                arr[index]=tmp;     //
                index++;
            }
        }
        tmp=arr[i];         //swap pivot
        arr[i]=arr[index];  //
        arr[index]=tmp;     //
        sort(arr,front,index-1);
        sort(arr,index+1,end);
    }
}

