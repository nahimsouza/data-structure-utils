/*

    A C / C++ program for Dijkstra's single source shortest path algorithm.
    The program is for adjacency matrix representation of the graph


    Dijkstra Shortest Path Algorithm
    
    

*/

 
#include <stdio.h>
 
// Number of vertices in the graph
#define MAX 100
#define FALSE 0
#define TRUE 1
#define INFINITE 1000000 // big number to represent Infinite
 
// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(double dist[], int sptSet[], int V)
{
   // Initialize min value
   double min = INFINITE;
   int min_index;
   int v;
   for (v = 0; v < V; v++)
     if (sptSet[v] == FALSE && dist[v] <= min)
         min = dist[v], min_index = v;
 
   return min_index;
}
 
// A utility function to print the constructed distance array
int printSolution(double dist[], int n)
{
   printf("Vertex   Distance from Source\n");
   int i;
   for (i = 0; i < n; i++)
      printf("%d \t\t %.2f\n", i, dist[i]);
}
 
// Function that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(double graph[MAX][MAX], int src, int V)
{
     double dist[V];   // The output array.  dist[i] will hold the shortest
                      // distance from src to i
 
     int sptSet[V]; // sptSet[i] will TRUE if vertex i is included in shortest
                     // path tree or shortest distance from src to i is finalized
 
     int i;
 
     // Initialize all distances as INFINITE and stpSet[] as FALSE
     for (i = 0; i < V; i++)
        dist[i] = INFINITE, sptSet[i] = FALSE;
 
     // Distance of source vertex from itself is always 0
     dist[src] = 0;
 
     int count;
 
     // Find shortest path for all vertices
     for (count = 0; count < V-1; count++)
     {
       // Pick the minimum distance vertex from the set of vertices not
       // yet processed. u is always equal to src in first iteration.
       int u = minDistance(dist, sptSet, V);
 
       // Mark the picked vertex as processed
       sptSet[u] = TRUE;
 
       // Update dist value of the adjacent vertices of the picked vertex.
       int v;
       for (v = 0; v < V; v++) {
 
         // Update dist[v] only if is not in sptSet, there is an edge from 
         // u to v, and total weight of path from src to  v through u is 
         // smaller than current value of dist[v]
         if (!sptSet[v] && graph[u][v] && dist[u] != INFINITE 
                                       && ((dist[u]+graph[u][v]) - (dist[u]*graph[u][v])) < dist[v]) {
            //dist[v] = dist[u] + graph[u][v];
            dist[v] = ((dist[u]+graph[u][v]) - (dist[u]*graph[u][v]));
         }
         
         //printf("u:%d, v:%d dist[v]:%.2f dist[u]+graph[u][v]:%.2f \n", u, v, dist[v], dist[u]+graph[u][v] );
       }
     }
 
     // print the constructed distance array
     printSolution(dist, V);
}
 
 
void addEdge(double graph[MAX][MAX], int u, int v, double weight) {
    graph[u][v] = weight;
    graph[v][u] = weight;
}
 

// driver program to test above function
int main()
{

    int n, m;
    int a, b;
    double p;
    int i;
    
    scanf("%d %d", &n, &m);
    
    while (n!=0 && m!=0) {
        double graph[MAX][MAX] = {INFINITE};
        
        for (i = 0; i < m; i++) {
            scanf("%d %d %lf", &a, &b, &p);
            addEdge(graph, a-1, b-1, p);
        }
        
        dijkstra(graph, 0, n);
        
        scanf("%d %d", &n, &m);
    }
 
    return 0;
}