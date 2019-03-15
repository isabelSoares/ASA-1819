int UGRAPHcc(Network Net, int cc[]) { 
   int id = 0;
   int vertices = Net->N;
   for (int v = 0; v < vertices; ++v) 
      cc[v] = -1;
   for (int v = 0; v < vertices; ++v)
      if (cc[v] == -1) 
         dfsRcc(Net, cc, v, id++);
   return id;
}

static void dfsRcc( Network Net, int cc[], int v, int id){ 
   cc[v] = id;
   for (link a = Net->adj[v]; a != NULL; a = a->next)
      if (cc[a->v] == -1) 
         dfsRcc( Net, cc, a->v, id); 
}