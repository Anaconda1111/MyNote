//
// Created by xcs on 2021-04-18.
//

#include "PriorityQueue.h"
PriorityQueue Initialize(int ListSize){
    PriorityQueue H=malloc(sizeof (struct HeapStruct));
    if (H==NULL){
        printf("Out of Space!\n");
        return NULL;
    }
    H->NodeValueList=malloc(sizeof (ElementType)*(ListSize+1));
    H->Size=0;
    H->Capacity=ListSize;
    H->NodeValueList[0]=INT_MIN;
    return H;
}

void MakeEmpty(PriorityQueue H){
    H->Size=0;
}

int IsFull(PriorityQueue H){
    return H->Size>=H->Capacity;
}

int IsEmpty(PriorityQueue H){
    return H->Size==0;
}

int Insert(ElementType X,PriorityQueue H){
    int i;
    if (IsFull(H)){
        printf("Heap is Full!\n");
        return RESULT_FAIL;
    }
    H->Size++;
    for (i = H->Size;X<H->NodeValueList[i/2];i/=2) {
        H->NodeValueList[i]=H->NodeValueList[i/2];
    }
    H->NodeValueList[i]=X;
    return RESULT_OK;
}

int DeleteMin(PriorityQueue H){
    int i,child;
    ElementType LastNum,MinData;
    if (IsEmpty(H)){
        printf("Heap Is Empty!\n");
        return RESULT_FAIL;
    }
    LastNum=H->NodeValueList[H->Size];
    MinData=H->NodeValueList[1];
    H->Size--;
    for (i=1;i*2<=H->Size;i=child) {
        child=i*2;
        if (child+1<=H->Size&&H->NodeValueList[child]>H->NodeValueList[child+1])
            child++;
        if (H->NodeValueList[child]<LastNum)
            H->NodeValueList[i]=H->NodeValueList[child];
        else
            break;  //如果父节点的两个子节点都比LastNum大，则该父节点的值用LastNum填充
    }
    H->NodeValueList[i]=LastNum;
    return MinData;
}

void PrintMinHeap(PriorityQueue H){
    if (IsEmpty(H)){
        printf("It's Empty!\n");
        return;
    }
    for (int i = 1; i <=H->Size ; ++i) {
        printf("%d\n",H->NodeValueList[i]);
    }
}

void ConvertToMinHeap(PriorityQueue H,int Position){
    if (Position*2*2<=H->Size)
        ConvertToMinHeap(H,Position*2);
    if ((Position*2+1)*2<=H->Size)
        ConvertToMinHeap(H,Position*2+1);
    if (Position*2+1<=H->Size&&H->NodeValueList[Position*2+1]<H->NodeValueList[Position*2]){
        if (H->NodeValueList[Position]>H->NodeValueList[Position*2+1]){
            ElementType Temp;
            Temp=H->NodeValueList[Position];
            H->NodeValueList[Position]=H->NodeValueList[Position*2+1];
            H->NodeValueList[Position*2+1]=Temp;
        }
    }
    else{
        if (H->NodeValueList[Position]>H->NodeValueList[Position*2]){
            ElementType Temp;
            Temp=H->NodeValueList[Position];
            H->NodeValueList[Position]=H->NodeValueList[Position*2];
            H->NodeValueList[Position*2]=Temp;
        }
    }
}