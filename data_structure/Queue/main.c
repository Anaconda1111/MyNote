#include "main.h"

int main() {
    Queue Q=CreateQueue();
    if (IsEmpty(Q)){
        printf("It's Empty!\n");
    }
    Enqueue(1,Q);
    Enqueue(2,Q);
    Enqueue(3,Q);
    Enqueue(17,Q);
    Show_the_Queue(Q);
    printf("%d\n",FrontAndDequeue(Q));
    Show_the_Queue(Q);
    if (!IsEmpty(Q)){
        printf("It's not Empty!\n");
    }
}
