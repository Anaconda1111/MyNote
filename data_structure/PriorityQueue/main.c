#include "PriorityQueue.h"
int main() {
    int SIZE=100;
    PriorityQueue H=Initialize(SIZE);
    ElementType normalArray[SIZE];
//    H->Size=10000;
    for (int i = 0; i < SIZE; ++i) {
        ElementType Temp=rand();
        normalArray[i]=Temp;
        H->NodeValueList[i+1]=Temp;
        H->Size++;
    }

    for (int i = SIZE-1 ;i>0; --i) {
        for (int j = 0; j < i; ++j) {
            if (normalArray[j]>normalArray[j+1]){
                ElementType temp=normalArray[j+1];
                normalArray[j+1]=normalArray[j];
                normalArray[j]=temp;
            }
        }
    }

    ConvertToMinHeap(H,1);
    PrintMinHeap(H);
    printf("%d",normalArray[0]);
    return 0;
}
