#include <stdio.h>
#include <stdlib.h>
#include "ROUTER.h"

typedef struct node *link;
Network NETWORKinit(int N, int M);
link InsertBegin(int v, link head);
void NETWORKinsertM(Network Net, int r1, int r2);
//int** MATRIXinit(int lines, int columns, int value);
void NETWORKinsert(Network Net, int r1, int r2);


struct node{
    int v;
    link next;
};

struct network{
    int N, M;
    link *adj;
};

int main(int argc, char const *argv[])
{
    int N,M,a,b;
    int i = 0;

    scanf("%d", &N);
    scanf("%d", &M);
    if ((N < 2) && (M < 1)){ fprintf(stderr,"Invalid number");}
    Network Net = NETWORKinit(N,M);
    for (i=0; i < M; i++){
        scanf("%d", &a);
        scanf("%d", &b);
        NETWORKinsertM(Net,a,b);
    }

    return 0;
}

Network NETWORKinit(int N, int M) {
    int i;
    Network Net = malloc(sizeof(struct network));
    Net->N = N;
    Net->M = 0;
    Net->adj = malloc(N * sizeof(link));
    for (i = 0; i < N; i++)
        Net->adj[i] = NULL;
    return Net;
}

link InsertBegin(int v, link head) {
    link x = malloc(sizeof(struct node));
    x->v = v;
    x ->next = head;
    return x;
}

void NETWORKinsertM(Network Net, int r1, int r2) {
    Net->adj[r1] = InsertBegin(r2, Net->adj[r1]);
    Net->adj[r2] = InsertBegin(r1, Net->adj[r2]);
}

void NETWORKinsert(Network Net, int r1, int r2) {
    if (Net->adj[r1][r2] == 0)
    Net->adj[r1][r2] = 1;
    Net->adj[r2][r1] = 1;
}

/*int** MATRIXinit(int lines, int columns, int value){
    int matrix[lines][columns];
    memset(matrix, 0, sizeof(matrix[0][0]) * lines * columns);
    return matrix;
}*/


