//
// Created by xcs on 2021-02-15.
//

#ifndef AVLTREE__AVLTREE_H_
#define AVLTREE__AVLTREE_H_

#define RESULT_OK     1
#define RESULT_FAIL   0
#define ElementType   int
#include "stdio.h"
#include "stdlib.h"

typedef struct AVLNode *Position;
typedef struct AVLNode *AVLTree;
struct AVLNode{
    ElementType  Data;
    AVLTree      Left;
    AVLTree      Right;
    int          Height;
};

AVLTree MakeEmpty(AVLTree T);
Position Find(ElementType X,AVLTree T);
Position FindMin(AVLTree T);
Position FindMax(AVLTree T);
int Max(int Height_of_Left,int Height_of_Right);
int Height(Position P);
Position SingleRotateWithLeft(Position K2);
Position SingleRotateWithRight(Position K2);
Position DoubleRotateWithLeft(Position K3);
Position DoubleRotateWithRight(Position K3);
AVLTree Insert(ElementType X,AVLTree T);
AVLTree Delete(ElementType X,AVLTree T);
void Inorder_Traversal(AVLTree T);

#endif//AVLTREE__AVLTREE_H_
