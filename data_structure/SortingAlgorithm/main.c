#include <stdio.h>
#include "Sort.h"



int main() {
    ElementType A[20] = {0,5,2,6,7,3,8,0};
    BucketSort(A,20);
    for (int i = 0; i < 20; ++i)
        printf("%d ",A[i]);
}


