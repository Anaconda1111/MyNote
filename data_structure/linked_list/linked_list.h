//
// Created by xcs on 2021-01-26.
//

#ifndef LINKED_LIST__LINKED_LIST_H_
#define LINKED_LIST__LINKED_LIST_H_
#include <stdlib.h>
#include <stdio.h>
#define ElementType Element
#define Element int
#define RESULT_OK 1
#define RESULT_FALID 0

typedef struct Node *PtrToNode;         //指向该结构体的指针
typedef PtrToNode List;                 //用于指向表头
typedef PtrToNode Position;             //用于表示当前指向的节点
struct Node{
    ElementType Data;                   //链表节点数据
    PtrToNode    Next;                  //链表指向下一个链表的指针
};

int IsEmpty(List L);
int IsLast(Position P,List L);
Position Find_By_Data(ElementType X,List L);
Position Find_By_Position(int X,List L);
Position FindPrevious(ElementType X,List L);
int Delete(ElementType X,List L);
int Insert(ElementType X,List L,Position P);
int DeleteList(List L);
int Creat_New_Node(ElementType X,List L);
void Show_the_Linked_List(List L);
#endif //LINKED_LIST__LINKED_LIST_H_
