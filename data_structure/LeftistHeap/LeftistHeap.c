//
// Created by xcs on 2021-04-19.
//

#include "LeftistHeap.h"

PriorityQueue Initialize(ElementType X){
    PriorityQueue H=malloc(sizeof (struct TreeNode));
    if (H==NULL){
        printf("Out Of Space!\n");
        return NULL;
    }
    H->Data=X;
    H->Left=NULL;
    H->Right=NULL;
    H->NPL=0;
    return H;
}

PriorityQueue Merge1(PriorityQueue H1,PriorityQueue H2){
    if (H1->Left==NULL){
        H1->Left=H2;
    }
    else{
        H1->Right=Merge(H1->Right,H2);
        if (H1->Left->NPL<H1->Right->NPL){
            PriorityQueue Temp;
            Temp=H1->Left;
            H1->Left=H2->Right;
            H2->Right=Temp;
            H1->NPL=H1->Right->NPL+1;
        }
    }
    return H1;
}

PriorityQueue Merge(PriorityQueue H1,PriorityQueue H2){
    if (H1==NULL)
        return H2;
    if (H2==NULL)
        return H1;
    if (H1->Data<H2->Data)
        return Merge1(H1,H2);
    else
        return Merge1(H2,H2);
}

PriorityQueue Insert(ElementType X,PriorityQueue H){
    PriorityQueue NewNode=malloc(sizeof (struct TreeNode));
    if (NewNode==NULL){
        printf("Out Of Space!\n");
        return NewNode;
    }
    NewNode->Data=X;
    NewNode->Left=NULL;
    NewNode->Right=NULL;
    NewNode->NPL=0;
    return Merge(H,NewNode);
}

PriorityQueue DeleteMin(PriorityQueue H){
    if (H==NULL){
        printf("It's Empty!\n");
        return NULL;
    }
    PriorityQueue LeftHeap,RightHeap;
    LeftHeap=H->Left;
    RightHeap=H->Right;
    free(H);
    return Merge(LeftHeap,RightHeap);
}

