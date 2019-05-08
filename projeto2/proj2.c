
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
 
int pushRelabel(int **C, int ** F, int source, int sink) {
  int *excess, *height, *list, *seen, i, p;
 
  excess = (int *) calloc(NODES, sizeof(int));
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


int G[10][10],visited[10],n;    //n is no of vertices and graph is sorted in array G[10][10]

 
void DFS(int i)
{
  int j;
	printf("\n%d",i);
    visited[i]=1;
	
	for(j=0;j<n;j++)
       if(!visited[j]&&G[i][j]==1)
            DFS(j);
}
 
int main(void) {
  int **flow, **capacities, i,j,k,l,o,d,c;

  int f, e, t, stcounter=1;
  scanf("%d", &f); //num fornecedores
  scanf("%d", &e); //num estacoes

  NODES = f + e*2 + 2;
  printf("estacoes/nodes %d %d\n", e, NODES);
  scanf("%d", &t); //num ligacoes

  flow = (int **) calloc(NODES, sizeof(int*));
  capacities = (int **) calloc(NODES, sizeof(int*));
  for (i = 0; i < NODES; i++) {
    flow[i] = (int *) calloc(NODES, sizeof(int));
    capacities[i] = (int *) calloc(NODES, sizeof(int));
  }

  for( j= 2; j<=f+1;j++){ /*fornecedores*/
    scanf("%d",&k);
    capacities[0][j]= k;
    }

  for( j= f+2; j<f+e+2;j++){ /*estacoes*/
    scanf("%d",&l);
    capacities[j][NODES-1-e+stcounter] = l; 
    printf("capc da estacao: %d %d %d\n", j, NODES-1-e+stcounter, l);
    stcounter++;
    }

  for( j= 0; j<t;j++){
    scanf("%d",&o);
    scanf("%d",&d);
    scanf("%d",&c);
    if (d == 1 && o >= f+2){
      capacities[o+e][d] = c;
      printf("caso especial %d %d %d\n",o+e,d,c);
    }
    else{
      capacities[o][d] = c;
      printf("cap %d %d %d\n", o,d,c);
    }
  }
 

  printf("Capacity:\n");

  printMatrix(capacities);
 
  printf("Max Flow:\n%d\n", pushRelabel(capacities, flow,0, 1));
 
  printf("Flows:\n");
  printMatrix(flow);


  // DFS para cortes mínimos 
  int m,y;
  printf("Enter number of vertices:");
   
	scanf("%d",&n);
 
    //read the adjecency matrix
	printf("\nEnter adjecency matrix of the graph:");
   
	for(i=0;i<n;i++)
       for(y=0;y<n;y++)
			scanf("%d",&G[m][y]);
 
    //visited is initialized to zero
   for(m=0;m<n;m++)
        visited[m]=0;
 
    DFS(0);
 
  return 0;
}