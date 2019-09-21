#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX 10000
int arr[MAX], num;

typedef struct linked_list {
    int value;
    struct linked_list* next;
} linked_list;

void push_back(linked_list** p, int val) {
    linked_list **q = p;
    linked_list *_new = malloc(sizeof(linked_list));
    if(!_new) {
        printf("malloc error");
        exit(1);
    }
    _new->value = val;
    if((*q == NULL)) {
        *q = _new;
    } else {
        while((*q)->next!=NULL) {
            q = &((*q)->next);
        }
        (*q)->next = _new;
        q = &((*q)->next);
    }
    (*q)->next = NULL;
}

void radix_sort() {
    int i, mx=arr[0]; //get the max value so as to know number of digits
    for(i=1; i<num; ++i) {
        if(arr[i] > mx)
            mx = arr[i];
    }

    linked_list *bucket[10], *p;
    int exp=1,ind,digit=1;
    while(mx/exp) {
        for(i=0; i<10; ++i) //initialize
            bucket[i] = NULL;
        for(i=0; i<num; ++i)
            push_back(&bucket[(arr[i]/exp)%10], arr[i]);
        ind=0;
        for(i=0; i<10; ++i) {
            for(p=bucket[i]; p!=NULL; p=p->next)
                arr[ind++]=p->value;
            free(bucket[i]);
        }
        exp*=10;
    }
}

int main() {
    int i, max;
    printf("Please input amount and max value: ");
    scanf("%d %d", &num, &max);
    if(num>MAX) {
        printf("the amount must < %d\n",MAX);
        return 0;
    }
    printf("orig order:\n");
    srand(time(NULL));
    for(i=0; i<num; ++i) {
        arr[i] = rand()%max + 1;
        printf(" %d",arr[i]);
    }
    printf("\n\n");
    radix_sort();
    printf("sorted order:\n");
    for(i=0; i<num; ++i) {
        printf(" %d",arr[i]);
    }
    printf("\n");
    return 0;
}
