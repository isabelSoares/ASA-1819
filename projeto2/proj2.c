

//Relabel To Front copiado

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
 
#define MIN(X,Y) X < Y ? X : Y
#define INFINITE 10000000

int NODES;
 
void push(int ** C, int ** F, int *excess, int u, int v) {
  int send = MIN(excess[u], C[u][v] - F[u][v]);
  F[u][v] += send;
  F[v][u] -= send;
  excess[u] -= send;
  excess[v] += send;
}
 
void relabel( int **C,  int ** F, int *height, int u) {
  int v;
  int min_height = INFINITE;
  for (v = 0; v < NODES; v++) {
    if (C[u][v] - F[u][v] > 0) {
      min_height = MIN(min_height, height[v]);
      height[u] = min_height + 1;
    }
  }
}
 
void discharge(int ** C, int ** F, int *excess, int *height, int *seen, int u) {
  while (excess[u] > 0) {
    if (seen[u] < NODES) {
      int v = seen[u];
      if ((C[u][v] - F[u][v] > 0) && (height[u] > height[v])){
        push(C, F, excess, u, v);
      }
      else
        seen[u] += 1;
    } else {
      relabel(C, F, height, u);
      seen[u] = 0;
    }
  }
}
 
void moveToFront(int i, int *A) {
  int temp = A[i];
  int n;
  for (n = i; n > 0; n--){
    A[n] = A[n-1];
  }
  A[0] = temp;
}
 
int pushRelabel(int ** C, int ** F, int *excess,int source, int sink) {
  int *height, *list, *seen, i, p;
 
  
  height = (int *) calloc(NODES, sizeof(int));
  seen = (int *) calloc(NODES, sizeof(int));
  list = (int *) calloc((NODES-2), sizeof(int));
 
  for (i = 0, p = 0; i < NODES; i++){
    if((i != source) && (i != sink)) {
      list[p] = i;
      p++;
    }
  }
 
  height[source] = NODES;
  excess[source] = INFINITE;
  for (i = 0; i < NODES; i++)
    push(C, F, excess, source, i);
 
  p = 0;
  while (p < NODES - 2) {
    int u = list[p];
    int old_height = height[u];
    discharge(C, F, excess, height, seen, u);
    if (height[u] > old_height) {
      moveToFront(p,list);
      p=0;
    }
    else
      p += 1;
  }
  int maxflow = 0;
  for (i = 0; i < NODES; i++)
    maxflow += F[source][i];
 
  free(list);
 
  free(seen);
  free(height);
  free(excess);
 
  return maxflow;
}
 
void printMatrix(int ** M) {
  int i,j;
  for (i = 0; i < NODES; i++) {
    for (j = 0; j < NODES; j++)
      printf("%d\t",M[i][j]);
    printf("\n");
  }
}
 
int main(void) {
  int *excess, **flow, **capacities, i,j,k,l,o,d,c;

  int f, e, t;
  scanf("%d", &f);
  scanf("%d", &e);

  NODES = f + e + 2;
  scanf("%d", &t);

  excess = (int *) calloc(NODES, sizeof(int));
  flow = (int **) calloc(NODES, sizeof(int*));
  capacities = (int **) calloc(NODES, sizeof(int*));
  for (i = 0; i < NODES; i++) {
    flow[i] = (int *) calloc(NODES, sizeof(int));
    capacities[i] = (int *) calloc(NODES, sizeof(int));
  }

  for( j= 2; j<f+1;j++){
    scanf("%d",&k);
    excess[j] = k;
    capacities[0][j]= 0;
    } /*excessos*/
  for( j= f+2; j<NODES;j++){
    scanf("%d",&l);
    excess[j] = l;
    }
  for( j= 0; j<t;j++){
    scanf("%d",&o);
    scanf("%d",&d);
    scanf("%d",&c);
    capacities[o][d] = c;
  }
 

  printf("Capacity:\n");

  printMatrix(capacities);
 
  printf("Max Flow:\n%d\n", pushRelabel(capacities, flow, excess,0, 1));
 
  printf("Flows:\n");
  printMatrix(flow);
 
  return 0;
}