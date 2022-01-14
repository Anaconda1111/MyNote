//
// Created by xcs on 2021-03-22.
//

#include "HashMap.h"
int IsPrimeNumber(int X){
    for (int i = 2; i < X; ++i) {
        if (X%i==0)
            return RESULT_FAIL;
    }
    return RESULT_OK;
}

int NextPrime(int X){
    while (!IsPrimeNumber(X))
        X++;
    return X;
}

unsigned int Hash(ElementType Key,int TableSize){
    return Key%TableSize;
}



#if USE_SEPARATE_CHAINING==1
HashTable  InitializeTable(int TableSize){
    HashTable H=malloc(sizeof (struct HashTbl));
    if (H==NULL){
        printf("Init Fail,Out of Space!\n");
        return NULL;
    }
    H->TableSize=NextPrime(TableSize);
    //为结构体指针数组分配空间
    H->TheLists=malloc(sizeof (List)*H->TableSize);
    if (H->TheLists==NULL){
        printf("Out of Space!\n");
        return H;
    }

    //为结构体指针数组中的每一个结构体指针分配空间
    for (int i = 0; i < H->TableSize; ++i) {
        H->TheLists[i]=malloc(sizeof (struct ListNode));
        if (H->TheLists[i]==NULL){
            printf("Out of Space!\n");
            break;
        }
        else
            H->TheLists[i]->Next=NULL;
    }
    return H;
}

Position Find(ElementType Key,HashTable H){
    Position P;
    List L=H->TheLists[Hash(Key,H->TableSize)];
    P=L->Next;
    while (P!=NULL){
        if (P->Key==Key)
            break;
        P=P->Next;
    }
    return P;
}

int Insert(ElementType Key,HashTable H){
    Position P,NewCell;
    P=Find(Key,H);
    if (P==NULL){
        NewCell=malloc(sizeof (struct ListNode));
        if (NewCell==NULL){
            printf("Out of Space!\n");
            return RESULT_FAIL;
        }
        else{
            List L=H->TheLists[Hash(Key,H->TableSize)];
            NewCell->Next=L->Next;
            NewCell->Key=Key;
            L->Next=NewCell;
            return RESULT_OK;
        }
    }
    else{
        printf("Node already exist!\n");
        return RESULT_FAIL;
    }
}

int Delete(ElementType Key,HashTable H){
    Position P;
    List L;
    L=H->TheLists[Hash(Key,H->TableSize)];
    while (L->Next!=NULL){
        if (L->Next->Key==Key)
            break;
    }
    if (L->Next!=NULL){
        P=L->Next;
        L->Next=P->Next;
        free(P);
        return RESULT_OK;
    }
    else
        return RESULT_FAIL;
}
#endif

#if USE_OPEN_ADDRESSING==1
HashTable InitializeTable(int TableSize){
    HashTable H=malloc(sizeof (struct HashTbl));
    if (H==NULL){
        printf("Out Of Space!\n");
        return NULL;
    }
    H->TableSize=NextPrime(TableSize);
    H->TheCells=malloc(sizeof (struct HashEntry)*H->TableSize);
    if (H->TheCells==NULL){
        printf("Out Of Space!\n");
        return H;
    }
    for (int i=0;i<H->TableSize;i++){
        H->TheCells[i].Info=Empty;
    }
    return H;
}

Position Find(ElementType Key,HashTable H){
    Position CurrentPOS;
    unsigned int DeviationNum=0;
    int CollisionNUM=0;
    CurrentPOS=Hash(Key,H->TableSize);
    while (H->TheCells[CurrentPOS+DeviationNum].Info!=Empty&&H->TheCells[CurrentPOS+DeviationNum].Key!=Key){
        if (DeviationNum==0)
            DeviationNum++;
        CollisionNUM++;
        DeviationNum<<=CollisionNUM-1;
        if ((CurrentPOS+DeviationNum)>=H->TableSize)
            CurrentPOS=(CurrentPOS+DeviationNum)-H->TableSize;
    }
    return CurrentPOS+DeviationNum;
}

int Insert(ElementType Key,HashTable H){
    Position P=Find(Key,H);
    if (H->TheCells[P].Info!=Legitimate){
        H->TheCells[P].Info=Legitimate;
        H->TheCells[P].Key=Key;
        return RESULT_OK;
    }
    else
        return RESULT_FAIL;
}

int DeleteHashEntry(ElementType Key,HashTable H){
    Position P=Find(Key,H);
    if (H->TheCells[P].Info!=Delete){
        H->TheCells[P].Info=Delete;
        return RESULT_OK;
    }
    else
        return RESULT_FAIL;
}

ElementType Retrieve(Position P,HashTable H){
    return H->TheCells[P].Key;
}

HashTable Rehash(HashTable H){
    int OldSize;
    Cell *OldCells;
    OldSize=H->TableSize;
    OldCells=H->TheCells;
    H=InitializeTable(2*OldSize);
    for (int i = 0; i < OldSize; ++i) {
        if (OldCells[i].Info==Legitimate)
            Insert(OldCells[i].Key,H);
    }
    free(OldCells);
    return H;
}
#endif