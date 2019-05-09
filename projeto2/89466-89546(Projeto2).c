#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <limits.h>
 
#define MINIMUM(X,Y) X < Y ? X : Y
#define INFINITE INT_MAX

int numvertices;

struct edge{
  int x,y;
};

int compare_function(const void *a,const void *b){
  int *x = (int *) a;
  int *y = (int *) b;
  return *x - *y;
}

int compare_function_edge(const void *a, const void *b){
  const struct edge *a1 = a;
  const struct edge *b1 = b;
  if (a1->x - b1->x != 0)
    return a1->x - b1->x;
  else
    return a1->y - b1->y;
}
 
void push(int **capacities, int **flows, int *excess, int u, int v){
  int sentflow = MINIMUM(excess[u], capacities[u][v] - flows[u][v]);
  /* envia o possivel (ou a quantidade que o arco ainda pode receber, ou o seu excesso, o que for menor)*/
  flows[v][u] -= sentflow;
  flows[u][v] += sentflow;
  excess[u] -= sentflow;
  excess[v] += sentflow;
}
 
void relabel( int **capacities,  int **flows, int *height, int u){
  /*aumenta a altura de um vertice caso ainda tenha excesso 
  aumenta a altura para 1+ menor altura do vertice ao qual tem uma ligacao onde ainda pode mandar flow*/
  int v;
  int min_height = INFINITE;
  for (v = 0; v < numvertices; v++) {
    if (capacities[u][v] - flows[u][v] > 0) {
      min_height = MINIMUM(min_height, height[v]);
      height[u] = min_height + 1;
    }
  }
}
 
void discharge(int **capacities, int **flows, int *excess, int *height, int *seen, int u){
  /*controla o que fazer a cada vertice, se tiver excesso e se houver algum vertice com altura menor, envia (push)
  senao, aumenta a sua altura para conseguir enviar (relabel)*/
  while(excess[u] > 0){
    if (seen[u] < numvertices){
      int v = seen[u];
      if ((capacities[u][v] - flows[u][v] > 0) && (height[u] > height[v]))
        push(capacities, flows, excess, u, v);
      else
        seen[u] += 1;
    }
    else{
      relabel(capacities, flows, height, u);
      seen[u] = 0;
    }
  }
}
 
void updateList(int i, int *list) {
  /*altera a lista - coloca o elemento i no primeiro lugar
  neste caso, se um vertice aumentar de altura, coloca o no topo da lista de vertices*/
  int p = list[i];
  int n;
  for (n = i; n > 0; n--){
    list[n] = list[n-1];
  }
  list[0] = p;
}
 
int relabelToFront(int **capacities, int ** flows, int source, int market) {
  int *excess, *height, *list, *seen, i, p=0;
 
  excess = (int *) calloc(numvertices, sizeof(int));
  height = (int *) calloc(numvertices, sizeof(int));
  seen = (int *) calloc(numvertices, sizeof(int));
  list = (int *) calloc((numvertices-2), sizeof(int));
 
  for (i = 0; i < numvertices; i++){
    if((i != source) && (i != market)) {
      list[p] = i;
      p++;
    }
  }
 
  height[source] = numvertices;
  excess[source] = INFINITE;
  for (i = 0; i < numvertices; i++)
    push(capacities, flows, excess, source, i);
 
  p = 0;
  while (p < numvertices-2){
    int u = list[p];
    int old_height = height[u];
    discharge(capacities, flows, excess, height, seen, u);
    if (height[u] > old_height){
      updateList(p,list);
      p=0;
    }
    else
      p += 1;
  }
  int maximumflow = 0;
  for (i = 0; i < numvertices; i++)
    maximumflow += flows[source][i];
 
  free(list);
  free(seen);
  free(height);
  free(excess);
 
  return maximumflow;
}
 
void printMatrix(int **M) {
  int i,j;
  for (i = 0; i < numvertices; i++) {
    for (j = 0; j < numvertices; j++)
      printf("%d ",M[i][j]);
    printf("\n");
  }
}


void DFS(int** G, int*visited ,int size ,int i){
  int j;
	visited[i]=1;
	
	for(j=0;j<size;j++)
    if(!visited[j] && G[i][j]){
      DFS(G,visited, size, j);
    }
}
 
int main(void) {
  int **flows, **capacities,**transposed , i,j,k,l,o,d,c,a;

  int f, e, connections, stcounter=1;
  a = scanf("%d", &f); /*numero de fornecedores*/
  a = scanf("%d", &e); /*numero de estacoes*/

  numvertices = f + e*2 + 2;
  a = scanf("%d", &connections); /*numero de ligacoes*/

  flows = (int **) calloc(numvertices, sizeof(int*));
  capacities = (int **) calloc(numvertices, sizeof(int*));
  transposed = (int **) calloc(numvertices, sizeof(int*));
  for (i = 0; i < numvertices; i++) {
    flows[i] = (int *) calloc(numvertices, sizeof(int));
    capacities[i] = (int *) calloc(numvertices, sizeof(int));
    transposed[i] = (int *) calloc(numvertices, sizeof(int));
  }

  for( j= 2; j<=f+1;j++){ /*fornecedores*/
    a = scanf("%d",&k);
    capacities[0][j]= k;
    }

  for( j= f+2; j<f+e+2;j++){ /*estacoes*/
    a = scanf("%d",&l);
    capacities[j][numvertices-1-e+stcounter] = l; 
    stcounter++;
    }
  for( j= 0; j<connections;j++){
    a = scanf("%d",&o);
    a = scanf("%d",&d);
    a = scanf("%d",&c);
    if (d == 1 && o >= f+2){
      capacities[o+e][d] = c;
    }
    else if (o >=f+2 && o <= f+e+1 && d >= f+2 && d <= f+e+1){
      capacities[o+e][d] = c;
    }
    else{
      capacities[o][d] = c;
    }
  }
  printf("%d\n", relabelToFront(capacities, flows,0,1));

  for (i=0; i< numvertices; i++)
    for(j=0; j<numvertices; j++){
      flows[i][j] = capacities[i][j] - flows[i][j];
    }
  
  for (i=0; i< numvertices; i++)
    for(j=0; j<numvertices; j++)
      transposed[j][i] = flows[i][j];
 
  int *visited;
  visited = (int *) calloc(numvertices, sizeof(int));
  DFS(transposed, visited,numvertices ,1);

  /*for (i=0; i<numvertices;i++)
   printf("visited: %d: %d\n", i,visited[i]);*/

int *cutstations, st_c=0, lig_c=0;
struct edge *cutedges;
cutstations = (int *) calloc(e, sizeof(int));
cutedges = (struct edge *) malloc(connections* sizeof(struct edge));
for(i=0;i<connections;i++){
  cutedges[i].x = 0;
  cutedges[i].y = 0;
}
 

  for (i = 0; i < numvertices; i++) 
      for (j = 0; j < numvertices; j++) 
         if ((visited[i] == 1 && visited[j] == 0 && capacities[i][j] != 0) || (visited[j] == 1 && visited[i] == 0 && capacities[i][j] != 0)){ /*if true , [i][j] faz parte do corte minimo*/
          /*printf("mincut: %d -> %d\n", i,j);*/
          if (j == i+e && i >= f+2 && i <= f+e+1){ /*estacao no corte minimo*/
            cutstations[st_c] = i;
            st_c++;
          }
          /*else if(i >= f+2 && i <= f+e+1 && j >= f+2 && j <= f+e+1){
            cutedges[lig_c].x = i;
            cutedges[lig_c].y = j;
            lig_c++;
          }*/
          else if(i >= f+e+2){ /*ligacao no corte minimo - auxiliar que envia */
            cutedges[lig_c].x = i-e;
            cutedges[lig_c].y = j;
            lig_c++;
          }
          else if(i >=2  && i <= f+1)/*ligacao no corte minimo - fornecedor que envia*/ {
            cutedges[lig_c].x = i;
            cutedges[lig_c].y = j;
            lig_c++;
          }
         }
/*
  printf("cutstations\n");
  for (i=0;i<e;i++){
    printf("%d ", cutstations[i]);
  }
    printf("cutedges\n");
  for (i=0;i<e;i++){
    printf("%d %d\n", cutedges[i].x, cutedges[i].y);
  }
*/

  qsort(cutstations, e, sizeof(int), compare_function);
  qsort(cutedges,connections,sizeof(struct edge), compare_function_edge);


  int augmentstations=0;
  for(i=0;i<e-1;i++)
    if(cutstations[i] != 0){
      printf("%d ", cutstations[i]);
      augmentstations++;
    }
  if(cutstations[e-1] != 0){
    printf("%d\n", cutstations[e-1]);
    augmentstations++;
  }
  if (augmentstations == 0) {printf("\n");}
  for(i=0;i<connections;i++)
    if(cutedges[i].x != 0)
      printf("%d %d\n",cutedges[i].x, cutedges[i].y);


  free(visited);
  free(cutstations);
  free(cutedges);
  for (i=0;i< numvertices;i++){
      free(capacities[i]);
      free(flows[i]);
      free(transposed[i]);
  }
  a=0;
  return a;
}