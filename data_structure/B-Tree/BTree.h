//
// Created by xcs on 2021-08-04.
//

#ifndef B_TREE__BTREE_H_
#define B_TREE__BTREE_H_
#include "stdio.h"
#include "stdlib.h"

#define ElementType int
#define MaxDegree 3

typedef struct BTreeNode* BTree;
typedef BTree Position;

struct BTreeNode{
    BTree Child[MaxDegree+1];
    BTree Father;
    ElementType Data[MaxDegree];
    unsigned short DataNum;
    unsigned short ChildNum;
};







BTree CreateNewTreeNode();
void SwitchNum(ElementType *X1,ElementType *X2);

#endif//B_TREE__BTREE_H_
