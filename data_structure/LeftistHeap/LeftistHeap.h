//
// Created by xcs on 2021-04-19.
//

#ifndef LEFTISTHEAP__LEFTISTHEAP_H_
#define LEFTISTHEAP__LEFTISTHEAP_H_
#include "stdlib.h"
#include "stdio.h"

#define ElementType int
#define RESULT_OK   1
#define RESULT_FAIL 0


typedef struct TreeNode *PriorityQueue;
struct TreeNode{
    ElementType Data;
    PriorityQueue Left;
    PriorityQueue Right;
    int NPL;
};
PriorityQueue Initialize(ElementType X);
PriorityQueue Merge1(PriorityQueue H1,PriorityQueue H2);
PriorityQueue Merge(PriorityQueue H1,PriorityQueue H2);
PriorityQueue Insert(ElementType X,PriorityQueue H);
PriorityQueue DeleteMin(PriorityQueue H);
#endif//LEFTISTHEAP__LEFTISTHEAP_H_
