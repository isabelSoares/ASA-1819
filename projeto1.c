#include <stdio.h>
#include <stdlib.h>


typedef struct node *link;
Network NETWORKinit(int N, int M);
link InsertBegin(int v, link head);
void NETWORKinsertM(Network Net, int r1, int r2);

struct node{
    int v;
    link next;
};

typedef struct Network{
    int N, M;
    link *adj;
}Network;

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

Network *NETWORKinit(int N, int M) {
    int i;
    Network *Net = (Network*) malloc(sizeof(struct Network));
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

void NETWORKinsertM(Network *Net, int r1, int r2) {
    Net->adj[r1] = InsertBegin(r2, Net->adj[r1]);
    Net->adj[r2] = InsertBegin(r1, Net->adj[r2]);
}


