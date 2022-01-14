#include "SearchTree.h"

SearchTree MakeEmpty(SearchTree T){
  if (T!=NULL){
    MakeEmpty(T->Right);
    MakeEmpty(T->Left);
    free(T);
  }
  return NULL;
}

Position Find(Element X,SearchTree T){
  if (T==NULL)
    return NULL;
  if (X<T->Data)
    Find(X,T->Left);
  else if (X>T->Data)
    Find(X,T->Right);
  else
    return T;
}

Position FindMin(SearchTree T){
  if (T!=NULL&&T->Left!=NULL)
    FindMin(T->Left);
  else
    return T;
}

Position FindMax(SearchTree T){
  if (T!=NULL&&T->Right!=NULL)
    FindMax(T->Right);
  else
    return T;
}

SearchTree Insert(Element X,SearchTree T){


  if (T==NULL){    //T==NULL意味着找到树上的空位
    T=malloc(sizeof (struct TreeNode));
    if (T==NULL){
      printf("Out of Space!\n");
      return T;
    }
    T->Data=X;
    T->Left=NULL;
    T->Right=NULL;
  }

  else if (X>T->Data)
    T->Right=Insert(X,T->Right);
  else if (X<T->Data)
    T->Left=Insert(X,T->Left);
  return T;
}

Position Delete(Element X,SearchTree T){
  if (T==NULL){
    printf("Error\n");
    return NULL;
  }


  if (T->Data<X)
    T->Right=Delete(X,T->Right);
  else if (T->Data>X)
    T->Left=Delete(X,T->Left);
  else{
    if (T->Left!=NULL&&T->Right!=NULL){
      Position Temp=FindMin(T->Right);
      T->Data=Temp->Data;
      T->Right=Delete(T->Data,T->Right);
    }
    else{
      Position Temp=T;
      if (T->Right!=NULL)
        T=T->Right;
      else if (T->Left!=NULL)
        T=T->Left;
      free(Temp);
    }
    return T;
  }
}

void Inorder_Traversal(SearchTree T){
  if (T!=NULL){
    Inorder_Traversal(T->Left);
    printf("%d\n",T->Data);
    Inorder_Traversal(T->Right);
  }
}