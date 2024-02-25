//
// Created by xcs on 2021-05-11.
//

#include "Sort.h"
#include "stdlib.h"
void Swap(ElementType *X1,ElementType *X2){
    ElementType temp=*(X1);
    *X1=*X2;
    *X2=temp;
}

void InsertionSort(ElementType A[],int n){
    int j;
    ElementType Temp;
    for (int i = 1; i < n; ++i) {
        Temp=A[i];
        for (j = i; j > 0; --j) {
            if (A[j-1]>Temp)
                A[j]=A[j-1];
            else
                break;
        }
        A[j]=Temp;
    }
}


void ShellSort(ElementType A[],int N){
    int j,Increment;
    ElementType Temp;
    for (Increment=N/2;Increment>0;Increment/=2) {
        for (int i = Increment; i < N; ++i) {
            Temp=A[i];
            for ( j = i; j-Increment >=0 ; j-=Increment) {
                if (A[j-Increment]>Temp)
                    A[j]=A[j-Increment];
                else
                    break;
            }
            A[j]=Temp;
        }
    }
}

/////////////////////堆排序//////////////////////////
#define LeftChild(i)  (i*2+1)

void PercDown(ElementType A[],int i,int N){
    int Child;
    ElementType temp;
    for (temp=A[i];LeftChild(i)<N;i=Child){
        Child=LeftChild(i);
        if (Child!=N-1&&A[Child+1]>A[Child])
            Child++;
        if (temp<A[Child])
            A[i]=A[Child];
        else
            break;
    }
    A[i]=temp;
}

void HeapSort(ElementType A[],int N){
    for (int i=N/2;i>=0;i--)
        PercDown(A,i,N);
    for (int i = N; i > 0; --i) {
        Swap(A,A+i-1);
        PercDown(A,0,i-1);
    }
}
////////////////////////////////////////////////////

/////////////////////归并排序/////////////////////////
void Merge(ElementType A[],ElementType temp[],int L_StartPosition,int R_StartPosition,int RightEnd){
    int LeftEnd,TempPosition,Num;
    LeftEnd=R_StartPosition-1;
    Num=RightEnd-L_StartPosition+1;
    TempPosition=L_StartPosition;
    while (L_StartPosition<=LeftEnd&&R_StartPosition<=RightEnd){
        if (A[L_StartPosition]<=A[R_StartPosition]){
            temp[TempPosition]=A[L_StartPosition];
            L_StartPosition++;
        }
        else{
            temp[TempPosition]=A[R_StartPosition];
            R_StartPosition++;
        }
        TempPosition++;
    }
    while (L_StartPosition<=LeftEnd){
        temp[TempPosition]=A[L_StartPosition];
        L_StartPosition++;
        TempPosition++;
    }

    while (R_StartPosition<=RightEnd){
        temp[TempPosition]=A[R_StartPosition];
        R_StartPosition++;
        TempPosition++;
    }

    for (int i = 0; i < Num; ++i,RightEnd--) {
        A[RightEnd]=temp[RightEnd];
    }
}


void Msort(ElementType A[],ElementType temp[],int Left,int Right){
    if (Left<Right){
        int Center=(Left+Right)/2;
        Msort(A,temp,Left,Center);
        Msort(A,temp,Center+1,Right);
        Merge(A,temp,Left,Center+1,Right);
    }
}

void MergeSort(ElementType A[],int Num){
    ElementType *TempArray=malloc(Num* sizeof(ElementType));
    Msort(A,TempArray,0,Num-1);
    free(TempArray);
}
////////////////////////////////////////////////////


//////////////////////快速排序////////////////////////
#define Cutoff 3

ElementType Median3(ElementType A[],int Left,int Right){
    int Center=(Left+Right)/2;
    if (A[Left]>A[Center])
        Swap(A+Left,A+Center);
    if (A[Left]>A[Right])
        Swap(A+Left,A+Right);
    if (A[Center]>A[Right])
        Swap(A+Center,A+Right);

    Swap(A+Center,A+Right-1);
    return A[Right-1];
}

void QSort(ElementType A[],int Left,int Right){
    if (Left+Cutoff<=Right){
        InsertionSort(A+Left,Right-Left+1);
        return;
    }
    ElementType Pivot=Median3(A,Left,Right);
    int i=Left+1,j=Right-2;
    for (;;) {
        while (A[i]<Pivot)
            i++;
        while (A[j]>Pivot)
            j++;
        if (i<j)
            Swap(A+i,A+j);
        else
            break;
    }
    Swap(A+i,A+Right-1);
    QSort(A,Left,i-1);
    QSort(A,i+1,Right);
}

void QuickSort(ElementType A[],int N){
    QSort(A,0,N-1);
}

////////////////////////////////////////////////////


//////////////////////桶排序/////////////////////////
void BucketSort(ElementType A[],int N){
    ElementType *Count=(ElementType *)malloc((N+1)* sizeof(ElementType));
    for(int i=0;i<N+1;i++)
        Count[i]=0;
    for (int i = 0; i < N; ++i)
        Count[A[i]]++;
    int index=0;
    for (int i = 0; i < N+1; ++i) {
        for (int j = 0; j < Count[i]; ++j) {
            A[index]=i;
            index++;
        }
    }
    free(Count);
}
////////////////////////////////////////////////////