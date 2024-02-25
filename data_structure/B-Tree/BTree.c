//
// Created by xcs on 2021-08-04.
//

#include "BTree.h"

BTree CreateNewTreeNode(){
    BTree NewNode=malloc(sizeof (struct BTreeNode));
    NewNode->DataNum=0;
    NewNode->ChildNum=0;
    for (unsigned short i = 0; i < MaxDegree+1; ++i) {
        NewNode->Child[i]=NULL;
    }
    return NewNode
}




BTree Insert(BTree T,BTree Father,ElementType X){
    if (T==NULL){
        T=CreateNewTreeNode();
        T->Data[0]=X;
        T->DataNum++;
        T->Father=Father;
        return T;
    } else if (T->ChildNum==0){
        T->Data[T->DataNum]=X;
        if (X<T->Data[T->DataNum-1])
            SwitchNum(T->Data+T->DataNum,T->Data+T->DataNum-1);
        T->DataNum++;
    }
    else {
        for (unsigned short i = 0; i <= T->DataNum; ++i) {
            if (i == T->DataNum) {
                T->Child[T->ChildNum - 1] = Insert(T->Child[T->ChildNum - 1], T, X);
            } else if (X < T->Data[i]) {
                T->Child[i] = Insert(T->Child[i], T, X);
                break;
            }
        }
    }
    if (T->DataNum==MaxDegree)


}


void SwitchTwoNum(ElementType *X1,ElementType *X2){
    ElementType temp=*X1;
    (*X1)=(*X2);
    (*X2)=temp;
}


void Split(BTree T,BTree Father){
    unsigned char i=MaxDegree/2;
    unsigned char j=0;
    Father->Data[Father->DataNum]=T->Data[MaxDegree/2];
    if (Father->Data[Father->DataNum]<Father->Data[Father->DataNum-1])
        SwitchTwoNum(Father->Data+Father->DataNum,Father->Data+Father->DataNum-1);
    Father->DataNum++;
    Father->Child[Father->ChildNum]=CreateNewTreeNode();
    while (i<MaxDegree){
        if (i>MaxDegree/2){
            Father->Child[Father->ChildNum]->Data[j]=T->Data[i];
            j++;
        }
        i++;
    }
}