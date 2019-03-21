#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node *link;
typedef struct network *Network;

struct network {
   int V; 
   int A; 
   link *adj; 
};

struct node { 
   int w; 
   link next; 
};

int min(int a,int b){return(a<b?a:b);}

/*funcao para comparar valores no quicksort*/
int cmpfunc (const void * a, const void * b) {return( *(int*)a - *(int*)b );}

static link NEWrouter(int w, link next) { 
   link a = malloc(sizeof(struct node));
   a->w = w; 
   a->next = next;     
   return a;                         
}

/*inicia uma rede com V vertices*/
Network NETWORKinit(int V) {
   int v;
   Network G = malloc(sizeof*G);
   G->V = V; 
   G->A = 0;
   G->adj = malloc(V* sizeof(link));
   for (v = 0; v < V; ++v) 
      G->adj[v] = NULL;
   return G;
}

/*adiciona uma coneccao entre routers da rede*/
void NETWORKinsertConnection(Network G, int v, int w) {
   G->adj[v-1] = NEWrouter(w-1, G->adj[v-1]);
   G->adj[w-1] = NEWrouter(v-1, G->adj[w-1]);
   G->A++;
}

/*liberta a rede de memoria*/
void NETWORKdestroy(Network G){
   int i;
   for(i = 0; i < G->V; i++) 
      free(G->adj[i]);
   free(G);
}

/*dfs auxiliar*/
void rDFS(Network G, int *cc, int v, int id){ 
   link a;
   cc[v] = id;
   for (a = G->adj[v]; a != NULL; a = a->next)
      if (cc[a->w] == -1) 
         rDFS(G, cc, a->w, id); 
}

/*funcao que retorna as componentes fortemente ligadas de uma rede*/
int NETWORKcompsligadas(Network G, int *cc){ 
   int id = 0;
   int v;
   for (v = 0; v < G->V; ++v) 
         cc[v] = -1;
   for (v = 0; v < G->V; ++v)
      if (cc[v] == -1) 
         rDFS( G, cc, v, id++);
   return id;
}

/*funcao que retorna as subredes de um grafo "eliminando" os vertices que quebrariam a rede*/
int NETWORKsubcompsligadas( Network G, int *cc){ 
   int id = 2;
   /* comeca a contar componentes a partir de 2 (1 sao os routers que quebram a rede)*/
   int v;
   for (v = 0; v < G->V; ++v) 
      if (cc[v] != 1)
         cc[v] = -1;
   for (v = 0; v < G->V; ++v)
      if (cc[v] == -1) 
         rDFS(G,cc,v,id++);
   return id;
}

/*funcao auxiliar para determinar os vertices que quebram as redes (Algoritmo de Tarjan)*/
void BrokenRoutersAux(Network G,int r ,int* visitado, int* des,int* pai,int* low,int* brknRouters){
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
          BrokenRoutersAux(G,temp->w,visitado,des,pai,low,brknRouters);
      low[r]= min(low[r],low[temp->w]);
         if(pai[r]==-1 && filhos>1)
             brknRouters[r]=1;
      if(pai[r]!=-1 && des[r]<=low[temp->w])
            brknRouters[r]=1;           
        }    
      else if(temp->w!=pai[r]){
            low[r]=min(low[r],des[temp->w]);
        }
       temp= temp->next;
      }
}

/*funcao que determina os vertices que quebram as redes (Algoritmo de Tarjan)*/
void BrokenRouters(Network G, int *cc){
   int i;
   int numbrokenrouters = 0;
   int size = G->V;
   int *des = (int*)malloc(sizeof(int)*size);
   int *visitado = (int*)malloc(sizeof(int)*size);
   int *pai = (int*)malloc(sizeof(int)*size);
   int *low = (int*)malloc(sizeof(int)*size);
   int *brknRouters = (int*)malloc(sizeof(int)*size);
   for(i=0;i<size;i++){
        visitado[i]=0;
        pai[i]=-1;
        brknRouters[i]=0;
   }
   for(i=0;i<size;i++)
      if(visitado[i]==0)
         BrokenRoutersAux(G,i,visitado,des,pai,low,brknRouters);

   printf("\n");
   for(i=0;i<size;i++)
         if(brknRouters[i]==1)
            numbrokenrouters++;
   printf("%d\n", numbrokenrouters);
   for (i=0; i<size; i++)
      if(brknRouters[i]==1)
         cc[i] = 1;
         /*assinala os vertices que quebram com o valor 1 para depois se fazer a segunda DFS*/
}

/*funcao que retorna os maiores identificadores de cada subrede*/
void subnetIdentifiers(Network G, int *cc, int numCC, int *ids){
   int i;
   for (i=0; i<G->V; i++)
      ids[cc[i]] = i;
}

/*retorna a quantidade de vezes que o elemento mais comum do array aparece
ordena a lista com quicksort e ignora os valores a 1 do array de componentes ligados (sao os routers que quebram)*/
void HighestFrequency(Network G, int* cc){
   qsort(cc, G->V,sizeof(int),cmpfunc);
   int maxfreq=0, freq=1;
   int i =0,j;
   while(cc[i] == 1) {i++;}
   for(j=i;j<G->V-1;j++){
      if(cc[j]==cc[j+1]){
         freq++;
         if(freq > maxfreq)
            maxfreq=freq;
      }
      else
         freq=1;
      }
      if (maxfreq == 0)
         maxfreq = 1;
   printf("%d\n", maxfreq);
}

int main(int argc, char const *argv[]){
   int N,M,r1,r2, a;
   a =scanf("%d", &N);
   a =scanf("%d", &M);
   Network G = NETWORKinit(N); /*inicia a rede*/
   int i;
   for (i=0; i < M; i++){
      a = scanf("%d", &r1);
      a = scanf("%d", &r2);
      NETWORKinsertConnection(G,r1,r2); /*input*/
   }
   int *cc = (int*)malloc(sizeof(int)*N); /*array para as componentes ligadas*/
   int numCC = NETWORKcompsligadas(G,cc); /*numCC = numero de componentes ligadas*/
   printf("%d\n", numCC);
   int *subnetworks = (int*)malloc(sizeof(int)*numCC); /*array de identificadores*/
   subnetIdentifiers(G,cc,numCC,subnetworks);
   qsort(subnetworks,numCC,sizeof(int),cmpfunc);
   for (i=0; i <numCC-1; i++)
      printf("%d ", subnetworks[i]+1);
   printf("%d", subnetworks[numCC-1] +1);
   memset(cc, 0, N*sizeof(cc[0]));
   BrokenRouters(G,cc);
   NETWORKsubcompsligadas(G,cc);
   HighestFrequency(G,cc);
   free(cc);
   NETWORKdestroy(G); /*free ao grafo*/
   a = 0;
   return a;
}