//
// Created by xcs on 2021-01-26.
//

#include "linked_list.h"

int IsEmpty(List L){
    if (L->Next==NULL)
        return RESULT_OK;
    else
        return RESULT_FALID;
}

int IsLast(Position P,List L){  //测试当前节点是否为链表末尾
    if (P->Next==NULL)
        return RESULT_OK;
    else
        return RESULT_FALID;
}

Position Find_By_Data(ElementType X,List L){
    Position P;
    P=L->Next;//将P赋值为指向第一个节点（非表头）的结构体指针
    while (P->Next!=NULL&&P->Data!=X){
        P=P->Next;
    }
    if (P->Data!=X)
        return NULL;
    else
        return P;
}

Position Find_By_Position(int X,List L) {
  Position Temp;
  Temp = L;
  int i;
  for (i = 0; i < X && Temp != NULL; ++i) {
    Temp = Temp->Next;
  }
  return Temp;
}


Position FindPrevious(ElementType X,List L){
  Position P;
  P=L;
  while (P->Next!=NULL&&P->Next->Data!=X)
    P=P->Next;
  return P;
}

int Delete(ElementType X,List L){
    Position P=FindPrevious(X,L);
    Position Temp;
    if (P->Next==NULL)
      return RESULT_FALID;
    Temp=P->Next;
    P->Next=Temp->Next;
    free(Temp);
    return RESULT_OK;
}

int Insert(ElementType X,List L,Position P){ //在P所指向的节点后插入新节点
  Position Temp;
  Temp=malloc(sizeof (struct Node));
  if (Temp==NULL)
    return RESULT_FALID;
  Temp->Data=X;
  Temp->Next=P->Next;
  P->Next=Temp;
  return RESULT_OK;
}

int DeleteList(List L){  //删除链表
  Position P,Temp;
  P=L->Next;
  L->Next=NULL;
  while (P!=NULL){
    Temp=P->Next;
    free(P);
    P=Temp->Next;
  }
  return RESULT_OK;
}

int Creat_New_Node(ElementType X,List L){
  Position New_Node,Temp;
  New_Node = malloc(sizeof (struct Node));
  if (New_Node==NULL)
    return RESULT_FALID;
  New_Node->Data=X;
  New_Node->Next=NULL;
  Temp=L;
  while (!IsLast(Temp,L))
      Temp=Temp->Next;
  Temp->Next=New_Node;
  return RESULT_OK;
}

void Show_the_Linked_List(List L){
  Position P=L->Next;
  while (P!=NULL){
    printf("%d\n",P->Data);
    P=P->Next;
  }
};

