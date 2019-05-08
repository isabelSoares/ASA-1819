#include <stdio.h>
#include <stdlib.h>

typedef struct node *link;
typedef struct edge *e_link;
typedef struct *Network

struct network{
   int V, E;
   link *adj;
   e_link edges; 
};

struct node{ 
   int value, height, excess;
   link next; 
};

struct edge{ 
    int u, v, flow, cap;
    e_link next;
}; 
  
Network NETWORKinit(int V, int E) {
    int v;
    Network G = malloc(sizeof*G);
    G->V = V; 
    G->E = E;
    G->adj = malloc(V* sizeof(link));
    for (v = 0; v < V; ++v) 
        G->adj[v] = NULL;
    G->edges = malloc(sizeof(edge));
    
    return G;
}
  
static link NEWrouter(int value, link next) { 
   link a = malloc(sizeof(struct node));
   a->value = value;
   a->height = 0; 
   a->next = next;     
   return a;                         
}

edge NEWedge(int u, int v, int flow, int capacity, e_link next) { 
   edge a = malloc(sizeof(struct edge));
   a->u = u; 
   a->v = v;
   a->flow = flow;
   a->capacity = capacity;
   a->next = next;
   return a;                         
}

void NETWORKinsertConnection(Network G, int v, int w, int flow, int capacity) {
   G->adj[v] = NEWrouter(w, G->adj[v]);
   G->edges = NEWedge(v, w,flow,capacity, G->edges);
}

e_link searchEdge(Network G, int)

void NETWORKdestroy(Network G){
   int i;
   for(i = 0; i < G->V; i++) 
      free(G->adj[i]);
   free(G);
}
  
void NETWORKpreflow(Network G, int s) 
{ 
    // Making h of source Vertex equal to no. of vertices 
    // Height of other vertices is 0. 
    G->adj[s]->height = G->V;
    e_link edge;
    // 
    for (e = G->edges; e != NULL; e = e->next){ 
        // If current edge goes from source 
        if (e->u == s){ 
            // Flow is equal to capacity 
            e->flow = e->capacity; 
  
            // Initialize excess flow for adjacent v 
            G->adj[e->v]->excess += e->flow;
  
            // Add an edge from v to s in residual graph with 
            // capacity equal to 0 
            NETWORKinsertConnection(G, e->v, s, -e->flow, 0);
        } 
    } 
} 
  
// returns index of overflowing Vertex 
int overFlowVertex(Network G){ 
    for (int i = 1; i < G->V - 1; i++) 
       if (G->adj[i]->excess > 0) 
            return i; 
    // -1 if no overflowing Vertex 
    return -1; 
} 
  
// Update reverse flow for flow added on ith Edge 
void updateReverseEdgeFlow(Network G, int i, int flow){ 
    int u = G->edges, v = edge[i].u; 
  
    for (int j = 0; j < edge.size(); j++) 
    { 
        if (edge[j].v == v && edge[j].u == u) 
        { 
            edge[j].flow -= flow; 
            return; 
        } 
    } 
  
    // adding reverse Edge in residual graph 
    Edge e = Edge(0, flow, u, v); 
    edge.push_back(e); 
} 
  
// To push flow from overflowing vertex u 
bool Graph::push(int u) 
{ 
    // Traverse through all edges to find an adjacent (of u) 
    // to which flow can be pushed 
    for (int i = 0; i < edge.size(); i++) 
    { 
        // Checks u of current edge is same as given 
        // overflowing vertex 
        if (edge[i].u == u) 
        { 
            // if flow is equal to capacity then no push 
            // is possible 
            if (edge[i].flow == edge[i].capacity) 
                continue; 
  
            // Push is only possible if height of adjacent 
            // is smaller than height of overflowing vertex 
            if (ver[u].h > ver[edge[i].v].h) 
            { 
                // Flow to be pushed is equal to minimum of 
                // remaining flow on edge and excess flow. 
                int flow = min(edge[i].capacity - edge[i].flow, 
                               ver[u].e_flow); 
  
                // Reduce excess flow for overflowing vertex 
                ver[u].e_flow -= flow; 
  
                // Increase excess flow for adjacent 
                ver[edge[i].v].e_flow += flow; 
  
                // Add residual flow (With capacity 0 and negative 
                // flow) 
                edge[i].flow += flow; 
  
                updateReverseEdgeFlow(i, flow); 
  
                return true; 
            } 
        } 
    } 
    return false; 
} 
  
// function to relabel vertex u 
void Graph::relabel(int u) 
{ 
    // Initialize minimum height of an adjacent 
    int mh = INT_MAX; 
  
    // Find the adjacent with minimum height 
    for (int i = 0; i < edge.size(); i++) 
    { 
        if (edge[i].u == u) 
        { 
            // if flow is equal to capacity then no 
            // relabeling 
            if (edge[i].flow == edge[i].capacity) 
                continue; 
  
            // Update minimum height 
            if (ver[edge[i].v].h < mh) 
            { 
                mh = ver[edge[i].v].h; 
  
                // updating height of u 
                ver[u].h = mh + 1; 
            } 
        } 
    } 
} 
  
// main function for printing maximum flow of graph 
int Graph::getMaxFlow(int s, int t) 
{ 
    preflow(s); 
  
    // loop untill none of the Vertex is in overflow 
    while (overFlowVertex(ver) != -1) 
    { 
        int u = overFlowVertex(ver); 
        if (!push(u)) 
            relabel(u); 
    } 
  
    // ver.back() returns last Vertex, whose 
    // e_flow will be final maximum flow 
    return ver.back().e_flow; 
} 
  
// Driver program to test above functions 
int main() 
{ 
    int V = 6; 
    Graph g(V); 
  
    // Creating above shown flow network 
    g.addEdge(0, 1, 16); 
    g.addEdge(0, 2, 13); 
    g.addEdge(1, 2, 10); 
    g.addEdge(2, 1, 4); 
    g.addEdge(1, 3, 12); 
    g.addEdge(2, 4, 14); 
    g.addEdge(3, 2, 9); 
    g.addEdge(3, 5, 20); 
    g.addEdge(4, 3, 7); 
    g.addEdge(4, 5, 4); 
  
    // Initialize source and sink 
    int s = 0, t = 5; 
  
    cout << "Maximum flow is " << g.getMaxFlow(s, t); 
    return 0; 
} 