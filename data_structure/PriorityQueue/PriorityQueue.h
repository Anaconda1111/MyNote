//
// Created by xcs on 2021-04-18.
//

#include "limits.h"
#include "stdlib.h"
#include "stdio.h"

#ifndef PRIORITYQUEUE__PRIORITYQUEUE_H_
#define PRIORITYQUEUE__PRIORITYQUEUE_H_
#define ElementType int
#define RESULT_OK     1
#define RESULT_FAIL   0

typedef struct HeapStruct* PriorityQueue;

struct HeapStruct{
    int Capacity;
    int Size;
    ElementType *NodeValueList;
};

PriorityQueue Initialize(int ListSize);
void MakeEmpty(PriorityQueue H);
int IsFull(PriorityQueue H);
int IsEmpty(PriorityQueue H);
int Insert(ElementType X,PriorityQueue H);
int DeleteMin(PriorityQueue H);
void PrintMinHeap(PriorityQueue H);
void ConvertToMinHeap(PriorityQueue H,int Position);
#endif//PRIORITYQUEUE__PRIORITYQUEUE_H_
