//
// Created by xcs on 2021-09-16.
//

#include "Queue.h"
#include "stdlib.h"
#include "stdio.h"
Q CreateNewQueue(int Size){
    Q NewQueue=(struct Queue *)malloc(sizeof (struct Queue));
    if (NewQueue==NULL){
        printf("Out Of Space!\n");
        return NULL;
    }
    NewQueue->VertexArray=(int *)malloc(Size*sizeof (int ));
    NewQueue->top=0;
    NewQueue->button=-1;
    NewQueue->num=0;
    NewQueue->maxsize=Size;
    return NewQueue;
}

void EnQueue(Q Queue,int X){
    if (Queue->num+1<=Queue->maxsize){
        Queue->num++;
        Queue->button++;
        if (Queue->button>=Queue->maxsize)
            Queue->button=0;
        Queue->VertexArray[Queue->button]=X;
    } else
        printf("Queue full!\n");
}

int DeQueue(Q Queue){
    if (!IsEmpty(Queue)){
        Queue->num--;
        int temp=Queue->VertexArray[Queue->top];
        Queue->top++;
        if (Queue->top>=Queue->maxsize)
            Queue->top=0;
        return temp;
    } else
        printf("Is Empty!\n");
}

int IsEmpty(Q Queue){
    return Queue->num==0;
}

void DeleteQueue(Q Queue){
    free(Queue->VertexArray);
    free(Queue);
}