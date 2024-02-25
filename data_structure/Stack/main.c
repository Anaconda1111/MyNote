#include "main.h"

int main(){
    Stack S=CreateStack();
    Pop(S);
    Push(1,S);
    Push(2,S);
    Push(4,S);
    Push(17,S);
    Show_the_Stack(S);
    Show_the_Stack(S);
    return 0;
}
