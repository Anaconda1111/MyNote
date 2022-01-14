//
// Created by xcs on 2021-09-16.
//

#ifndef GRAPH__QUEUE_H_
#define GRAPH__QUEUE_H_
typedef struct Queue * Q;
struct Queue{
    int top;
    int button;
    int maxsize;
    int *VertexArray;
    int num;
};

Q CreateNewQueue(int Size);
void EnQueue(Q Queue,int X);
int DeQueue(Q Queue);
int IsEmpty(Q Queue);
void DeleteQueue(Q Queue);


#endif//GRAPH__QUEUE_H_