//
// Created by xcs on 2021-09-12.
//

#ifndef GRAPH__GRAPH_H_
#define GRAPH__GRAPH_H_
#include "stdlib.h"
#include "stdio.h"
#include "limits.h"
#include "Queue.h"

#define ElementType int
#define Infinity  INT_MAX

typedef struct Graph *G;
typedef struct PathInformation *P;


struct Graph{
    int Index;
    G Next;
    P PathInformationHead;
};

struct PathInformation{
    int PointIndex;
    int Weigh;
    P  Next;
};


void AddNewPath(P Header,int index,int weight);
void DeletePath(P Header,int index);
void AddNewVertex(G Header,int index);
void DeleteVertex(G Header,int index);
void AddPathInformation(G Header,int index1,int index2,int weight);
void DeletePathInformation(G Header,int index1,int index2,int weight);
int Unweighted(int VertexNum,int Vertex1,int Vertex2,G Header);
int Dijkstra(int VertexNum,int index1,int index2,G Header);
G FindV(G Header,int index);
#endif//GRAPH__GRAPH_H_
