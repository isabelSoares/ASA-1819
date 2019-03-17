#include <stdio.h>
#include <stdlib.h>

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

static link NEWnode( int w, link next) { 
   link a = malloc( sizeof (struct node));
   a->w = w; 
   a->next = next;     
   return a;                         
}

Network NETWORKinit(int V) { 
   Network G = malloc(sizeof *G);
   G->V = V; 
   G->A = 0;
   G->adj = malloc((V) * sizeof (link));
   for (int v = 0; v < V; ++v) 
      G->adj[v] = NULL;
   return G;
}

void NETWORKinsertArc(Network G, int v, int w) { 
   for (link a = G->adj[v]; a != NULL; a = a->next) 
      if (a->w == w) return;
   G->adj[v-1] = NEWnode( w-1, G->adj[v-1]);
   G->adj[w-1] = NEWnode( v-1, G->adj[w-1]);
   G->A++;
}

void dfsRcc( Network G, int *cc, int v, int id){ 
   cc[v] = id;
   for (link a = G->adj[v]; a != NULL; a = a->next)
      if (cc[a->w] == -1) 
         dfsRcc(G, cc, a->w, id); 
}

int NETWORKcc( Network G, int *cc){ 
   int id = 0;
   for (int v = 0; v < G->V; ++v) 
      cc[v] = -1;
   for (int v = 0; v < G->V; ++v)
      if (cc[v] == -1) 
         dfsRcc( G, cc, v, id++);
   return id;
}

void printNETWORK(Network G){
   int v;
   int V = G->V;
   for (v = 0; v < G->V; ++v){
        link head = G->adj[v]; 
        printf("VÉRTICE %d\n head ", v); 
        while (head) 
        { 
            printf("-> %d", head->w); 
            head = head->next; 
        } 
        printf("\n"); 
   }
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

void BrokenRouters(Network G){
    int i;
    int size = G->V;
    int des[size], visitado[size], pai[size], low[size], routerspartidos[size];
    for(i=0;i<size;i++){
        visitado[i]=0;
        pai[i]=-1;
        routerspartidos[i]=0;
    }
    for(i=0;i<size;i++){
      if(visitado[i]==0){
         BrokenRoutersAux(G,i,visitado,des,pai,low,routerspartidos);
        }
    }
    printf("\n");
    int flag=0;
    printf("Routers que podem causar sub-redes: \n");
    for(i=0;i<size;i++){
         if(routerspartidos[i]==1){
	         flag=1;
	         printf("Router: %d\n",i);
	      }
      }
    if(flag==0)
	printf("Nenhum router\n");
}

void identificadores(Network G, int *cc, int numCC, int *ids){
   int i, j;
   int routermax = 0;
   for(j=0; j < numCC ;j++)
      for (i=0; i<G->V; i++){
         if (cc[i] == j)
            ids[j] = i;
      }
}

int maximum(int * array, int size){

  int curr = 0;
  int max = 0;

  for(curr = 0; curr < size; curr++){
    if(array[curr] > max){ max = array[curr]; }
  }
}

void countingSort(int* array, int size){
  int curr = 0;
  int max = maximum(array, size);
  int * counting_array = calloc(max, sizeof(int));

  for(curr = 0; curr < size; curr ++){
    counting_array[array[curr]]++;
  }

  int num = 0;
  curr = 0;

  while(curr <= size){
    while(counting_array[num] > 0){
      array[curr] = num;
      counting_array[num]--;
      curr++;
      if(curr > size){ break; }
    }
    num++;
  }
}


int main(int argc, char const *argv[]){
   Network G = NETWORKinit(6);
   NETWORKinsertArc(G,1,4);
   NETWORKinsertArc(G,2,3);


   int i;
   int cc[G->V];
   int numCC = NETWORKcc(G,cc);
   printf("nº de subredes: %d\n", numCC);
   for (i=0; i < G->V; i++)
      printf("%d\n", cc[i]);
   int subredes[numCC];
   printf("\n");
   identificadores(G,cc,numCC,subredes);
   countingSort(subredes,numCC);
   for (i=0; i <numCC; i++)
      printf("%d\n", subredes[i]);

   printNETWORK(G);
   BrokenRouters(G);
   return 0;
}

//FALTA CONSEGUIR COLOCAR O GRAFO A COMEÇAR EM 1