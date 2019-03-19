#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node *link;
struct network {
   int V; 
   int A; 
   link *adj; 
};

typedef struct network *Network;


struct node { 
   int w; 
   link next; 
};



int min(int a,int b){return(a<b?a:b);}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

static link NEWnode(int w, link next) { 
   link a = malloc(sizeof(struct node));
   a->w = w; 
   a->next = next;     
   return a;                         
}

Network NETWORKinit(int V) {
   int v;
   Network G = malloc(sizeof *G);
   G->V = V; 
   G->A = 0;
   G->adj = malloc((V) * sizeof (link));
   for (v = 0; v < V; ++v) 
      G->adj[v] = NULL;
   return G;
}

void NETWORKinsertArc(Network G, int v, int w) {
   G->adj[v-1] = NEWnode(w-1, G->adj[v-1]);
   G->adj[w-1] = NEWnode(v-1, G->adj[w-1]);
   G->A++;
}

void dfsRcc( Network G, int *cc, int v, int id){ 
   link a;
   cc[v] = id;
   for (a = G->adj[v]; a != NULL; a = a->next)
      if (cc[a->w] == -1) 
         dfsRcc(G, cc, a->w, id); 
}

int NETWORKcc( Network G, int *cc){ 
   int id = 0;
   int v;
   for (v = 0; v < G->V; ++v) 
         cc[v] = -1;
   for (v = 0; v < G->V; ++v)
      if (cc[v] == -1) 
         dfsRcc( G, cc, v, id++);
   return id;
}

int aNETWORKcc( Network G, int *cc){ 
   int id = 2;
   int v;
   for (v = 0; v < G->V; ++v) 
      if (cc[v] != 1)
         cc[v] = -1;
   for (v = 0; v < G->V; ++v)
      if (cc[v] == -1) 
         dfsRcc( G, cc, v, id++);
   return id;
}

void printNETWORK(Network G){
   int v;
   for (v = 0; v < G->V; ++v){
        link head = G->adj[v]; 
        printf("VÉRTICE %d\n head ", v+1); 
        while (head) 
        { 
            printf("-> %d", head->w+1); 
            head = head->next; 
        } 
        printf("\n"); 
   }
}

void deleteEdge(Network G, int r1, int r2){
   link head = G->adj[r1];
   if (head == NULL) 
      return; 
   link temp = head; 
    if (head->w == r2){
        G->adj[r1] = G->adj[r1]->next;
        free(temp);
        return; 
    }
   while(temp->next != NULL && temp->next->w != r2) 
        temp = temp->next;
   if(temp->next == NULL)  {return;}
    link next = temp->next->next; 
    free(temp->next);
    temp->next = next;
}

void deleteBothEdges(Network G, int r1, int r2){
   deleteEdge(G,r1,r2);
   deleteEdge(G,r2,r1);
}

void BrokenRoutersAux(Network G,int r ,int* visitado, int* des,int* pai,int* low,int* routerspartidos){
    link temp=NULL;
    static int time=0;
    int filhos=0;
    temp = G->adj[r];
    visitado[r]=1;
    time++;
    des[r]=low[r]=time;

    while(temp!=NULL){       
       if(!visitado[temp->w]){
          filhos++;
          pai[temp->w]=r;
          BrokenRoutersAux(G,temp->w,visitado,des,pai,low,routerspartidos);

      low[r]= min(low[r],low[temp->w]);

          if(pai[r]==-1 && filhos>1)
             routerspartidos[r]=1;

      if(pai[r]!=-1 && des[r]<=low[temp->w])
            routerspartidos[r]=1;           
        }    
        else if(temp->w!=pai[r])
        {
            low[r]=min(low[r],des[temp->w]);
        }
       temp= temp->next;
      }

}

void BrokenRouters(Network G, int *cc){
   int i;
   int numbrokenrouters = 0;
   int size = G->V;
   int *des = (int*)malloc(sizeof(int)*size);
   int *visitado = (int*)malloc(sizeof(int)*size);
   int *pai = (int*)malloc(sizeof(int)*size);
   int *low = (int*)malloc(sizeof(int)*size);
   int *routerspartidos = (int*)malloc(sizeof(int)*size);
   for(i=0;i<size;i++){
        visitado[i]=0;
        pai[i]=-1;
        routerspartidos[i]=0;
    }
    for(i=0;i<size;i++)
      if(visitado[i]==0)
         BrokenRoutersAux(G,i,visitado,des,pai,low,routerspartidos);

    printf("\n");
    for(i=0;i<size;i++){
         if(routerspartidos[i]==1){
	         /*printf("Router: %d\n",i);*/
            numbrokenrouters++;
	      }
      }
   printf("%d\n", numbrokenrouters);
   for (i=0; i<size; i++){
      if(routerspartidos[i]==1)
         cc[i] = 1;
      }
   }

   

void subnetID(Network G, int *cc, int numCC, int *ids){
   int i, j;
   for(j=0; j < numCC ;j++)
      for (i=0; i<G->V; i++){
         if (cc[i] == j)
            ids[j] = i;
      }
}

int maximum(int *array, int size){

  int curr = 0;
  int max = 0;

  for(curr = 0; curr < size; curr++){
    if(array[curr] > max){ max = array[curr]; }
  }
  return max;
}

void countingSort(int *arr, int n, int exp) 
{ 
    int *output = (int*)malloc(sizeof(int)*n);
    int i; 
    int *count = (int*)calloc(10, sizeof(int)); 
    for (i = 0; i < n; i++) 
        count[ (arr[i]/exp)%10 ]++; 
    for (i = 1; i < 10; i++) 
        count[i] += count[i - 1]; 
    for (i = n - 1; i >= 0; i--) 
    { 
        output[count[ (arr[i]/exp)%10 ] - 1] = arr[i]; 
        count[ (arr[i]/exp)%10 ]--; 
    }
    for (i = 0; i < n; i++) 
        arr[i] = output[i]; 
} 

void radixsort(int *arr, int n){ 
   int e;
   int m = maximum(arr, n); 
   for (e = 1; m/e > 0; e *= 10) 
      countingSort(arr, n, e); 
}

void HighestFrequency(Network G, int* cc){
   radixsort(cc, G->V);
   int maxfreq=0, freq=1;
   int i =0,j;
   while(cc[i] == 1) {i++;}
   for(j=i;j<G->V-1;j++){
      if(cc[j]==cc[j+1]){
         freq++;
         if(freq > maxfreq){
            maxfreq=freq;
         }
      }
      else
         freq=1;
      }
   printf("%d\n", maxfreq);
}


int main(int argc, char const *argv[]){
   int N,M,r1,r2, a;
   a =scanf("%d", &N);
   a =scanf("%d", &M);
   /*if ((N < 2) && (M < 1)){ fprintf(stderr,"Invalid number");}*/
   Network G = NETWORKinit(N);
   int i;
   for (i=0; i < M; i++){
      a = scanf("%d", &r1);
      a = scanf("%d", &r2);
      NETWORKinsertArc(G,r1,r2);
   }
   int *cc = (int*)malloc(sizeof(int)*N); 
   int numCC = NETWORKcc(G,cc);

   printf("%d\n", numCC);
   int *subnetworks = (int*)malloc(sizeof(int)*numCC);
   subnetID(G,cc,numCC,subnetworks);
   radixsort(subnetworks,numCC);
   for (i=0; i <numCC-1; i++)
      printf("%d ", subnetworks[i]+1);
   printf("%d", subnetworks[numCC-1] +1);


   /*printNETWORK(G);*/
   memset(cc, 0, N*sizeof(cc[0]));
   BrokenRouters(G,cc);
   /*printNETWORK(G);*/

   aNETWORKcc(G,cc);
   HighestFrequency(G,cc);
   free(cc);
   a = 0;
   return a;
}