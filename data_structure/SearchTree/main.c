#include "main.h"
#include "time.h"
int main() {
    SearchTree T=NULL;
    T=Insert(6,T);
    T=Insert(2,T);
    T=Insert(8,T);
    T=Insert(1,T);
    T=Insert(5,T);
    T=Insert(3,T);
    T=Insert(4,T);
    Inorder_Traversal(T);
//    Delete(2,T);
//    Inorder_Traversal(T);
//    int SIZE=500000;
//    int TIMES=1000;
//    Element Data[SIZE];
//    SearchTree T=NULL;
//    clock_t start,finish;
//    clock_t totalTime;
//    int i,j;
//    for (i = 0; i < SIZE; ++i) {
//      Element Temp=rand();
//      Data[i]=Temp;
//      T=Insert(Temp,T);
//    }
//
//
//    Element min=Data[0];
//    start=clock();
//    for (j= 0; j<TIMES; ++j) {
//      for (i = 0; i < SIZE; ++i) {
//        if (min > Data[i])
//          min = Data[i];
//      }
//    }
//    printf("%d\n",min);
//    finish=clock();
//    totalTime=finish-start;
//    printf("Array:%ld ms\n",totalTime);
//
//    start=clock();
//    for (j = 0; j <TIMES; ++j) {
//      min=FindMin(T)->Data;
//    }
//    printf("%d\n",min);
//    finish=clock();
//    totalTime=finish-start;
//    printf("Searchtree:%ld ms",totalTime);
    return 0;
}


