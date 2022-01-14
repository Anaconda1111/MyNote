#include "Graph.h"
#include "string.h"
#define MAX 1024
int main() {
    struct Graph Header;
    Header.Next=NULL;
    AddNewVertex(&Header,1);
    AddNewVertex(&Header,2);
    AddNewVertex(&Header,3);
    AddNewVertex(&Header,4);
    AddNewVertex(&Header,5);
    AddNewVertex(&Header,6);
    AddNewVertex(&Header,7);
    AddPathInformation(&Header,1,2,2);
    AddPathInformation(&Header,1,4,1);
    AddPathInformation(&Header,2,4,3);
    AddPathInformation(&Header,2,5,10);
    AddPathInformation(&Header,3,1,4);
    AddPathInformation(&Header,3,6,5);
    AddPathInformation(&Header,4,3,2);
    AddPathInformation(&Header,4,5,2);
    AddPathInformation(&Header,4,6,8);
    AddPathInformation(&Header,4,7,4);
    AddPathInformation(&Header,5,7,6);
    AddPathInformation(&Header,7,6,1);
    printf("%d\n",Dijkstra(7,3,7,&Header));
    return 0;
}
