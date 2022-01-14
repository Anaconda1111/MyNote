#include "AVLTree.h"

int main() {
    AVLTree T=NULL;
    T=Insert(10,T);
    T=Insert(9,T);
    T=Insert(12,T);
    T=Insert(11,T);
    T=Insert(13,T);
  //  printf("%d\n",T->Data);
    T=Delete(12,T);
    T=Delete(9,T);
    printf("%d\n",T->Data);
    return 0;
}
