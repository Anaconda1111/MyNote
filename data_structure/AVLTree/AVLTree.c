#include "AVLTree.h"

AVLTree MakeEmpty(AVLTree T){
    if (T!=NULL){
        MakeEmpty(T->Left);
        MakeEmpty(T->Right);
        free(T);
    }
    return NULL;
}

Position Find(ElementType X,AVLTree T){
    if (T==NULL){
        printf("Can't not find this value in Tree!\n");
        return NULL;
    }
    else if (X>T->Data)
        Find(X,T->Right);
    else if (X<T->Data)
        Find(X,T->Left);
    else
        return T;
}

Position FindMin(AVLTree T){
    if (T!=NULL&&T->Left!=NULL)
        FindMin(T->Left);
    else
        return T;
}

Position FindMax(AVLTree T){
    if (T!=NULL&&T->Right!=NULL)
        FindMax(T->Right);
    else
        return T;
}

int Height(Position P){
    if (P==NULL)
        return -1;
    else
        return P->Height;
}

int Max(int Height_of_Left,int Height_of_Right){
    return Height_of_Left>Height_of_Right?Height_of_Left:Height_of_Right;
}

Position SingleRotateWithLeft(Position K2){
    Position K1;
    K1=K2->Left;
    K2->Left=K1->Right;
    K1->Right=K2;
    K2->Height=Max(Height(K2->Left),Height(K2->Right))+1;
    K1->Height=Max(Height(K1->Left),Height(K2))+1;
    return K1;
}

Position SingleRotateWithRight(Position K2){
    Position K1;
    K1=K2->Right;
    K2->Right=K1->Left;
    K1->Left=K2;
    K2->Height=Max(Height(K2->Left),Height(K2->Right))+1;
    K1->Height=Max(Height(K1->Right),Height(K2))+1;
    return K1;
}

Position DoubleRotateWithLeft(Position K3){  //针对左儿子的右子树插入后破坏AVL树特性的情况
    K3->Left=SingleRotateWithRight(K3->Left);//这种情况下，先对K3的左子树进行右边单旋转，使其变为左-左形式，然后执
    return SingleRotateWithLeft(K3);         // 行左边单旋转完成双旋转，即 1.对引起不平衡的根节点的左子树做右边单旋转
                                             // 2. 对该根节点做左边单旋转
}

Position DoubleRotateWithRight(Position K3){   //针对右儿子的左子树插入后破坏AVL特性的情况
    K3->Right=SingleRotateWithLeft(K3->Right); //这种情况下先对K3的右子树进行左边单旋转，使其变为右-右形式，然后
    return SingleRotateWithRight(K3);          //执行右边单旋转完成双旋转
}


AVLTree Insert(ElementType X,AVLTree T){
    if (T==NULL){
        T=malloc(sizeof (struct AVLNode));
        if (T==NULL){
            printf("Out of Space!\n");
            return T;
        }
        T->Data=X;
        T->Left=NULL;
        T->Right=NULL;
        T->Height=0;
    }
    else if (X>T->Data){
        T->Right=Insert(X,T->Right);
        if ((Height(T->Right)-Height(T->Left))>=2){
            if (X>T->Right->Data)
                T=SingleRotateWithRight(T);
            else
                T=DoubleRotateWithRight(T);
        }
    }
    else if (X<T->Data){
        T->Left=Insert(X,T->Left);
        if ((Height(T->Left)-Height(T->Right))>=2){
            if (X<T->Left->Data)
                T=SingleRotateWithLeft(T);
            else
                T=DoubleRotateWithLeft(T);
        }
    }
    T->Height=Max(Height(T->Left),Height(T->Right))+1;
    return T;
}

AVLTree Delete(ElementType X,AVLTree T){
    if (T==NULL){
        printf("Can't find this value in Tree!\n");
        return T;
    }
    else if (X>T->Data){
        T->Right=Delete(X,T->Right);
        if ((Height(T->Left)-Height(T->Right))>=2){
            if (Height(T->Left->Left)>Height(T->Left->Right))
                T=SingleRotateWithLeft(T);
            else
                T=DoubleRotateWithLeft(T);
            T->Height=Max(Height(T->Left),Height(T->Right))+1;
        }
    }
    else if (X<T->Data){
        T->Left=Delete(X,T->Left);
        if ((Height(T->Right)-Height(T->Left))>=2){
            if (Height(T->Right->Right)>Height(T->Right->Left))
                T=SingleRotateWithRight(T);
            else
                T=DoubleRotateWithRight(T);
            T->Height=Max(Height(T->Left),Height(T->Right))+1;
        }
    }
    else{
        if (T->Left!=NULL&&T->Right!=NULL){
            Position P=FindMin(T->Right);
            T->Data=P->Data;
            T->Right=Delete(T->Data,T->Right);
            if ((Height(T->Left)-Height(T->Right))>=2){
                if (Height(T->Left->Left)>Height(T->Left->Right))
                    T=SingleRotateWithLeft(T);
                else
                    T=DoubleRotateWithLeft(T);
                T->Height=Max(Height(T->Left),Height(T->Right))+1;
            }
        }
        else if (T->Left!=NULL){
            T->Data=T->Left->Data;
            free(T->Left);
            T->Left=NULL;
            if ((Height(T->Right)-Height(T->Left))>=2){
                if (Height(T->Right->Right)>Height(T->Right->Left))
                    T=SingleRotateWithRight(T);
                else
                    T=DoubleRotateWithRight(T);
                T->Height=Max(Height(T->Left),Height(T->Right))+1;
            }
        }
        else if (T->Right!=NULL){
            T->Data=T->Right->Data;
            free(T->Right);
            T->Right=NULL;
            if ((Height(T->Left)-Height(T->Right))>=2){
                if (Height(T->Left->Left)>Height(T->Left->Right))
                    T=SingleRotateWithLeft(T);
                else
                    T=DoubleRotateWithLeft(T);
                T->Height=Max(Height(T->Left),Height(T->Right))+1;
            }
        }
        else{
            free(T);
            T=NULL;
        }
    }
    return T;
}

void Inorder_Traversal(AVLTree T){
    if (T!=NULL){
        Inorder_Traversal(T->Left);
        printf("%d\n",T->Data);
        Inorder_Traversal(T->Right);
    }
}