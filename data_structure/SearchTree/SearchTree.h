//
// Created by xcs on 2021-02-04.
//

#ifndef SEARCHTREE__SEARCHTREE_H_
#define SEARCHTREE__SEARCHTREE_H_
#include <stdlib.h>
#include <stdio.h>

#define Element int
#define RESULT_OK    1
#define RESULT_FAIL 0

typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;
struct TreeNode{
    Element Data;
    SearchTree Left;
    SearchTree Right;
};

SearchTree MakeEmpty(SearchTree T);
Position Find(Element X,SearchTree T);
Position FindMin(SearchTree T);
Position FindMax(SearchTree T);
SearchTree Insert(Element X,SearchTree T);
SearchTree Delete(Element X,SearchTree T);
void Inorder_Traversal(SearchTree T);

#endif//SEARCHTREE__SEARCHTREE_H_
