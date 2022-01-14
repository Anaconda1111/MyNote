//
// Created by xcs on 2021-03-22.
//
#include "Config.h"
#include "stdlib.h"
#include "stdio.h"
#ifndef HASHMAP__HASHMAP_H_
#define HASHMAP__HASHMAP_H_
#define RESULT_OK   1
#define RESULT_FAIL 0
#define ElementType unsigned int

#if USE_SEPARATE_CHAINING==1
typedef struct ListNode *Position;
typedef Position List;
typedef struct HashTbl *HashTable;

struct ListNode{
    ElementType Key;
    Position Next;
};

struct HashTbl{
    int TableSize;
    List  *TheLists;//指向链表数组头节点的指针
};
HashTable  InitializeTable(int TableSize);
Position Find(ElementType Key,HashTable H);
int Insert(ElementType Key,HashTable H);
int Delete(ElementType Key,HashTable H);

#endif

#if USE_OPEN_ADDRESSING==1
typedef unsigned int Index;
typedef Index Position;
typedef struct HashTbl *HashTable;
typedef struct HashEntry Cell;
enum KindOfEntry{Legitimate,Empty,Delete};
struct HashEntry{
    ElementType Key;
    enum KindOfEntry Info;
};

struct HashTbl{
    int TableSize;
    Cell *TheCells;
};

HashTable InitializeTable(int TableSize);
Position Find(ElementType Key,HashTable H);
int Insert(ElementType Key,HashTable H);
int DeleteHashEntry(ElementType Key,HashTable H);
ElementType Retrieve(Position P,HashTable H);
HashTable Rehash(HashTable H);
#endif

#endif//HASHMAP__HASHMAP_H_
