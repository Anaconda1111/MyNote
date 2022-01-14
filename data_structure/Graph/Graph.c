//
// Created by xcs on 2021-09-12.
//

#include "Graph.h"
void AddNewPath(P Header,int index,int weight){
    P Temp=Header;
    while (Temp->Next!=NULL){
        if (index==Temp->Next->PointIndex){
            printf("Error,Index already exist!\n");
            return;
        }
        Temp=Temp->Next;
    }
    P NewPath=(struct PathInformation *)malloc(sizeof (struct PathInformation));
    if (NewPath==NULL){
        printf("Out of Space!\n");
        return;
    }
    NewPath->PointIndex=index;
    NewPath->Weigh=weight;
    NewPath->Next=NULL;
    Temp->Next=NewPath;
}

void DeletePath(P Header,int index){
    P Temp=Header;
    while (Temp!=NULL&&Temp->Next!=NULL){
        if (Temp->Next->PointIndex==index)
            break;
        Temp=Temp->Next;
    }
    if (Temp==NULL||Temp->Next==NULL){
        printf("Error,Can't Found!\n");
        return;
    }
    P DeleteOne=Temp->Next;
    Temp->Next=DeleteOne->Next;
    free(DeleteOne);
    DeleteOne=NULL;
}

void DestoryAllPathMessage(P Header){
    P Temp=Header;
    while (Temp!=NULL){
        Header=Header->Next;
        free(Temp);
        Temp=Header;
    }
}


void AddNewVertex(G Header,int index){
    G Temp=Header;
    while (Temp->Next!=NULL)
        Temp=Temp->Next;
    G NewVertex=(struct Graph *)malloc(sizeof (struct Graph));
    if (NewVertex==NULL){
        printf("Out of Space!\n");
        return;
    }
    NewVertex->Index=index;
    NewVertex->Next=NULL;
    NewVertex->PathInformationHead=(struct PathInformation *)malloc(sizeof (struct PathInformation));
    NewVertex->PathInformationHead->Next=NULL;
    Temp->Next=NewVertex;
}

void DeleteVertex(G Header,int index){
    G Temp=Header;
    while (Temp!=NULL&&Temp->Next!=NULL){
        if (Temp->Next->Index!=index)
            Temp=Temp->Next;
    }
    if (Temp==NULL||Temp->Next==NULL){
        printf("Error! Can't Find This Vertex!\n");
        return;
    }
    G DeletedVertex=Temp->Next;
    Temp->Next=DeletedVertex->Next;
    DestoryAllPathMessage(DeletedVertex->PathInformationHead);
    free(DeletedVertex);
}

void AddPathInformation(G Header,int index1,int index2,int weight){
    G V=FindV(Header,index1);
    AddNewPath(V->PathInformationHead,index2,weight);
}

void DeletePathInformation(G Header,int index1,int index2,int weight){
    G V=FindV(Header,index1);
    AddNewPath(V->PathInformationHead,index2,weight);
}

G FindV(G Header,int index){
    G Temp=Header->Next;
    while (Temp!=NULL&&Temp->Index!=index)
        Temp=Temp->Next;
    return Temp;
}


int Unweighted(int VertexNum,int Vertex1,int Vertex2,G Header){
    int **Table=(int **)malloc(VertexNum*sizeof (int *));
    for (int i = 0; i < VertexNum; ++i) {
        Table[i]=(int *)malloc(3*sizeof (int ));
        Table[i][0]=0;
        Table[i][1]=Infinity;
        Table[i][2]=0;
    }
    Table[Vertex1-1][1]=0;

    Q Queue=CreateNewQueue(VertexNum);
    G StartVertex=FindV(Header,Vertex1);
    EnQueue(Queue,StartVertex->Index);
    while (!IsEmpty(Queue)){
        int index_temp=DeQueue(Queue);
        G Graph_temp=FindV(Header,index_temp);
        Table[index_temp-1][0]=1;
        if (Graph_temp!=NULL){
            P Path_temp=Graph_temp->PathInformationHead->Next;
            while (Path_temp!=NULL){
                if (Table[Path_temp->PointIndex-1][1]==Infinity){
                    Table[Path_temp->PointIndex-1][1]=Table[index_temp-1][1]+1;
                }
                if (Table[Path_temp->PointIndex-1][0]==0){
                    Table[Path_temp->PointIndex-1][0]=1;
                    EnQueue(Queue,Path_temp->PointIndex);
                }
                Path_temp=Path_temp->Next;
            }
        }
    }
    int Answer=Table[Vertex2-1][1];
    for (int i = 0; i < VertexNum; ++i) {
        free(Table[i]);
    }
    free(Table);
    DeleteQueue(Queue);
    return Answer;
}

int Dijkstra(int VertexNum,int index1,int index2,G Header){
    int Answer;
    int **Table=(int **)malloc(VertexNum*sizeof (int *));
    for (int i = 0; i < VertexNum; ++i) {
        Table[i]=(int *)malloc(3*sizeof (int ));
        Table[i][0]=0;
        Table[i][1]=Infinity;
        Table[i][2]=0;
    }
    Q Queue=CreateNewQueue(VertexNum);
    G StartVertex=FindV(Header,index1);
    EnQueue(Queue,StartVertex->Index);
    Table[StartVertex->Index-1][1]=0;
    while (!IsEmpty(Queue)){
        int index_temp=DeQueue(Queue);
        G Graph_temp=FindV(Header,index_temp);
        //Table[Graph_temp->Index-1][0]=1;
        if (Graph_temp!=NULL){
            P Path_temp=Graph_temp->PathInformationHead->Next;
            while (Path_temp!=NULL){
                if (Table[index_temp-1][1]+Path_temp->Weigh<Table[Path_temp->PointIndex-1][1]){
                    Table[Path_temp->PointIndex-1][1]=Table[index_temp-1][1]+Path_temp->Weigh;
                }
                if (Table[Path_temp->PointIndex-1][0]==0){
                    Table[Path_temp->PointIndex-1][0]=1;
                    EnQueue(Queue,Path_temp->PointIndex);
                }
                Path_temp=Path_temp->Next;
            }
        }
    }
    Answer=Table[index2-1][1];
    for (int i = 0; i < VertexNum; ++i) {
        free(Table[i]);
    }
    free(Table);
    DeleteQueue(Queue);
    return Answer;
}