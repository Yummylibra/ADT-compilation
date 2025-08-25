/*
 * Graph algorithms.
 *
 * Author (of starter code): A. Tafliovich.
 */

#include <limits.h>

#include "graph.h"
#include "minheap.h"

#define NOTHING -1
#define DEBUG 0

typedef struct records {
  int numVertices;    // total number of vertices in the graph
                      // vertex IDs are 0, 1, ..., numVertices-1
  MinHeap* heap;      // priority queue
  bool* finished;     // finished[id] is true iff vertex id is finished
                      //   i.e. no longer in the PQ
  int* predecessors;  // predecessors[id] is the predecessor of vertex id
  Edge* tree;         // keeps edges for the resulting tree
  int numTreeEdges;   // current number of edges in mst
} Records;



/* Creates, populates, and returns a MinHeap to be used by Prim's and
 * Dijkstra's algorithms on Graph 'graph' starting from vertex with ID
 * 'startVertex'.
 * Precondition: 'startVertex' is valid in 'graph'
 */
MinHeap* initHeap(Graph* graph, int startVertex){
  if(graph == NULL || startVertex < 0 || startVertex >= graph->numVertices){
    return NULL;
  }

  MinHeap* min_heap = newHeap(graph->numVertices);
  if(min_heap == NULL) return NULL;
  for (int i = 0; i < graph->numVertices; i++){
        if (i == startVertex){//dist(start, start) = 0
            insert(min_heap, 0, startVertex);
        }else{
            insert(min_heap, INT_MAX, i);//dist(start, v) = inf
        }
    }

    return min_heap;
}

/* Creates, populates, and returns all records needed to run Prim's and
 * Dijkstra's algorithms on Graph 'graph' starting from vertex with ID
 * 'startVertex'.
 * Precondition: 'startVertex' is valid in 'graph'
 */
Records* initRecords(Graph* graph, int startVertex){
  if(graph == NULL || startVertex < 0 || startVertex >= graph->numVertices){
    return NULL;
  }

  Records* records = (Records*)malloc(sizeof(Records));
  
  records->numVertices = graph->numVertices;
  records->heap = initHeap(graph,startVertex);
  records->finished = (bool*)malloc(graph->numVertices * sizeof(bool));
  records->predecessors = (int*)malloc(graph->numVertices * sizeof(int));
  records->tree = (Edge*)malloc((graph->numVertices - 1) * sizeof(Edge));//MST is a tree, |E| = |V| - 1
  records->numTreeEdges = 0;

  for (int i = 0; i < graph->numVertices; i++) {
        records->finished[i] = false;//at the beginning, no vertices are finished
        records->predecessors[i] = NOTHING;//at the beginning, no vertices have predecessors
  }
  return records;
}

/* Returns true iff 'heap' is NULL or is empty. */
bool isEmpty(MinHeap* heap){
 return(heap == NULL || heap->size == 0);
}

/* Add a new edge to records at index ind. */
void addTreeEdge(Records* records, int ind, int fromVertex, int toVertex, int weight){
  if (ind >= 0 && ind < records->numVertices) {
    records->tree[ind].fromVertex = fromVertex;
    records->tree[ind].toVertex = toVertex;
    records->tree[ind].weight = weight;
  }
}

EdgeList* reverseList(EdgeList* head){
  EdgeList* prev = NULL;
  EdgeList* current = head;
  EdgeList* next = NULL;
  while (current != NULL){
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }
  return prev;
}

/* Creates and returns a path from 'vertex' to 'startVertex' from edges
 * in the distance tree 'distTree'.
 */
EdgeList* makePath(Edge* distTree, int vertex, int startVertex){
    if(distTree == NULL || vertex < 0 || startVertex < 0){
      return NULL;
    }
    EdgeList* path = NULL;
    int current_vertex = vertex;
    while(current_vertex != startVertex){
      int i = 0;
      while(distTree[i].toVertex != current_vertex){
        i++;
      }

      Edge* current_edge = &distTree[i];

      int previous_vertex = current_edge->fromVertex;
      int j = 0;
      while(previous_vertex != startVertex && distTree[j].toVertex != previous_vertex){
        j++;
      }

      Edge* previous_edge = &distTree[j];

      Edge* result_edge = (Edge*)malloc(sizeof(Edge));
      EdgeList* edgeNode = (EdgeList*)malloc(sizeof(EdgeList));
      result_edge->fromVertex = current_edge->toVertex;
      result_edge->toVertex = current_edge->fromVertex;
      result_edge->weight = current_edge->weight - previous_edge->weight;

      edgeNode->edge = result_edge;
      edgeNode->next = path;
      path = edgeNode;

      current_vertex = current_edge->fromVertex;

      
    }

    return reverseList(path);
}




/* Runs Prim's algorithm on Graph 'graph' starting from vertex with ID
 * 'startVertex', and return the resulting MST: an array of Edges.
 * Returns NULL is 'startVertex' is not valid in 'graph'.
 * Precondition: 'graph' is connected.
 */
Edge* getMSTprim(Graph* graph, int startVertex){
  if(graph == 0 || startVertex < 0 || startVertex >= graph->numVertices){
    return NULL;
  }

  Records* records = initRecords(graph, startVertex);//T = null, PQ = new minHeap, start = startVertex, PQ initialized

  while(!isEmpty(records->heap)){//while PQ.isNotEmpty()
    HeapNode u = extractMin(records->heap);//u = PQ.extractMin()
    int u_id = u.id;
    records->finished[u_id] = true;//dequeue u from PQ, u finished.

    if(records->predecessors[u_id] != NOTHING){//T.add(u, u.pred)
      //addTreeEdge(Records* records, int ind, int fromVertex, int toVertex, int weight)
      addTreeEdge(records, records->numTreeEdges, records->predecessors[u_id], u_id, u.priority);
      records->numTreeEdges++;
    }

    EdgeList* u_adjList = graph->vertices[u_id]->adjList;//for each vertex v in u's adjacency list:
    
    while(u_adjList != NULL){//adjlist a linked list, use while loop till end
      int v_id = u_adjList->edge->toVertex;
      if(!records->finished[v_id] && u_adjList->edge->weight < getPriority(records->heap, v_id)){//if v in PQ and weight(u,v) < priority(v)
        decreasePriority(records->heap, v_id, u_adjList->edge->weight);//PQ.decreasePriority(v, weight(u,v))
        records->predecessors[v_id] = u_id;//v.pred = u
      }
      u_adjList = u_adjList->next;
    }
    
  }//PQ is empty after this line
  Edge* mst = records->tree;//recoreds.tree restores every edge of MST
  deleteHeap(records->heap);
  free(records->finished);
  free(records->predecessors);
  free(records);
  return mst;

}

/* Runs Dijkstra's algorithm on Graph 'graph' starting from vertex with ID
 * 'startVertex', and return the resulting distance tree: an array of edges.
 * Returns NULL if 'startVertex' is not valid in 'graph'.
 * Precondition: 'graph' is connected.
 */
Edge* getDistanceTreeDijkstra(Graph* graph, int startVertex){
  if(graph == 0 || startVertex < 0 || startVertex >= graph->numVertices){
    return NULL;
  }

  Records* records = initRecords(graph, startVertex);//T = null, PQ = new minHeap, start = startVertex, PQ initialized
  int* distance = (int*)malloc(graph->numVertices*sizeof(int));
  for(int i = 0; i < graph->numVertices; i++){
    distance[i] = INT_MAX;
  }
  distance[startVertex] = 0;//start.distance = 0; for each vertex v != start, v.distance = inf

  while(!isEmpty(records->heap)){//while PQ.isNotEmpty()
    HeapNode u = extractMin(records->heap);//u = PQ.extractMin()
    int u_id = u.id;
    records->finished[u_id] = true;//dequeue u from PQ, u finished.

    EdgeList* u_adjList = graph->vertices[u_id]->adjList;//for each vertex v in u's adjacency list:
    while(u_adjList != NULL){
      int v_id = u_adjList->edge->toVertex;
      int new_distance = distance[u_id] + u_adjList->edge->weight;//new_distance = u.distance + weight(u,v)
      if(!records->finished[v_id] && new_distance < getPriority(records->heap, v_id)){//if v in PQ and new_distance < v.distance = priority(v)
        decreasePriority(records->heap, v_id, new_distance);//PQ.decreasePriority(v, new_distance)
        distance[v_id] = new_distance;//v.distance = new_distance
        records->predecessors[v_id] = u_id;//v.pred = u
      }
      u_adjList = u_adjList->next;
    }

  }
  // printf("we successfully construct a distance[] and predecessors[]\n");

  //want to have tree = {(u1,v1, d1), (u2,v2,d2)......}

  for(int i = 0; i < graph->numVertices; i++){
    if(records->predecessors[i] != NOTHING){
      //addTreeEdge(Records* records, int ind, int fromVertex, int toVertex, int weight)
      addTreeEdge(records,records->numTreeEdges, records->predecessors[i], i, distance[i]);
      records->numTreeEdges ++;
    }
    else{
      addTreeEdge(records,records->numTreeEdges, i, i, 0);
      records->numTreeEdges ++;
    }
  }

  Edge* distanceTree = records->tree; 
  
  // for(int i = 0; i < records->numTreeEdges; i++){
  //   printf("distanceTree[%d] : %d---%d, weight %d\n",i, distanceTree[i].fromVertex, distanceTree[i].toVertex,distanceTree[i].weight);
  // }

  free(distance);
  deleteHeap(records->heap);
  free(records->finished);
  free(records->predecessors);
  free(records);
  return distanceTree;

}

/* Creates and returns an array 'paths' of shortest paths from every vertex
 * in the graph to vertex 'startVertex', based on the information in the
 * distance tree 'distTree' produced by Dijkstra's algorithm on a graph with
 * 'numVertices' vertices and with the start vertex 'startVertex'.  paths[id]
 * is the list of edges of the form
 *   [(id -- id_1, w_0), (id_1 -- id_2, w_1), ..., (id_n -- start, w_n)]
 *   where w_0 + w_1 + ... + w_n = distance(id)
 * Returns NULL if 'startVertex' is not valid in 'distTree'.
 */
EdgeList** getShortestPaths(Edge* distTree, int numVertices, int startVertex){
  if(distTree == NULL || numVertices < 0 || startVertex > numVertices){
    return NULL;
  }
  
  EdgeList** shortestPaths = (EdgeList**)malloc(numVertices*sizeof(EdgeList*));
  for(int i = 0; i <  numVertices; i ++){
    shortestPaths[i] = NULL;
  }

  for(int i = 0; i < numVertices; i ++){
    if(i != startVertex){
      //EdgeList* makePath(Edge* distTree, int vertex, int startVertex)
      shortestPaths[i] = makePath(distTree, i, startVertex);
    }
  }
  return shortestPaths;
}


void printRecords(Records* records) {
  if (records == NULL) return;

  int numVertices = records->numVertices;
  printf("Reporting on algorithm's records on %d vertices...\n", numVertices);

  printf("The PQ is:\n");
  printHeap(records->heap);

  printf("The finished array is:\n");
  for (int i = 0; i < numVertices; i++)
    printf("\t%d: %d\n", i, records->finished[i]);

  printf("The predecessors array is:\n");
  for (int i = 0; i < numVertices; i++)
    printf("\t%d: %d\n", i, records->predecessors[i]);

  printf("The TREE edges are:\n");
  for (int i = 0; i < records->numTreeEdges; i++) printEdge(&records->tree[i]);

  printf("... done.\n");
}
