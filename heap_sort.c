#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX 10000
int arr[MAX], num, max;

void swap(int a1, int a2)
{
    int tmp = arr[a1];
    arr[a1] = arr[a2];
    arr[a2] = tmp;
}

void heapfy(int index, int end_node)
{
    int i, left, right;
    left = index * 2 + 1;
    right = left + 1;
    while(right > end_node) {   //handle end node
        if(left == end_node && arr[left] > arr[index]) {
            swap(left, index);
        }
        index--;
        left -= 2;
        right -= 2;
    }
    while(index >= 0) {     //build max heap tree
        if(arr[left] > arr[right] && arr[left] > arr[index]) {
            swap(left, index);
        } else if(arr[right] >= arr[left] && arr[right] > arr[index]){
            swap(right, index);
        }
        index--;
        left -= 2;
        right -= 2;
    }
}

void heap_sort() {
    int pow_2 = 2, node_num = 1, end_node = num - 1;
    while(pow_2 - 1 < num) {
        pow_2 *= 2;
    }
    pow_2 = pow_2 / 2 - 2;
    while(end_node > 0) {
        heapfy(pow_2, end_node);
        swap(0, end_node);
        end_node--;
        if(end_node == pow_2){
            pow_2 = pow_2 / 2 - 1;
        }
    }
}

int main() {
    int i;
    printf("please input amount and max value:");
    scanf("%d %d", &num, &max);
    if(num > MAX) {
        printf("the amount of numbers must < %d", MAX);
        return 0;
    }
    srand(time(NULL));
    printf("orig order:\n");
    for(i = 0; i < num; ++i) {
        arr[i] = rand() % max+1;
        printf("%5d", arr[i]);
    }
    printf("\n");
    heap_sort();

    printf("sorted order:\n");
    for(i = 0; i < num; ++i) {
        printf("%5d", arr[i]);
    }
    printf("\n");
    return 0;
}
