

#include "graph.h"


void printEdge(Edge* edge) {
  if (edge == NULL)
    printf("NULL");
  else
    printf("(%d -- %d, %d)", edge->fromVertex, edge->toVertex, edge->weight);
}

void printEdgeList(EdgeList* head) {
  while (head != NULL) {
    printEdge(head->edge);
    printf(" --> ");
    head = head->next;
  }
  printf("NULL");
}

void printVertex(Vertex* vertex) {
  if (vertex == NULL) {
    printf("NULL");
  } else {
    printf("%d: ", vertex->id);
    printEdgeList(vertex->adjList);
  }
}

void printGraph(Graph* graph) {
  if (graph == NULL) {
    printf("NULL");
    return;
  }
  printf("Number of vertices: %d. Number of edges: %d.\n\n", graph->numVertices,
         graph->numEdges);

  for (int i = 0; i < graph->numVertices; i++) {
    printVertex(graph->vertices[i]);
    printf("\n");
  }
  printf("\n");
}




/* Returns a newly created Edge from vertex with ID 'fromVertex' to vertex
 * with ID 'toVertex', with weight 'weight'.
 */
Edge* newEdge(int fromVertex, int toVertex, int weight){
  Edge* edge = (Edge*)malloc(sizeof(Edge));
  edge->fromVertex = fromVertex;
  edge->toVertex = toVertex;
  edge->weight = weight;
  return edge;
}

/* Returns a newly created EdgeList containing 'edge' and pointing to the next
 * EdgeList node 'next'.
 */
EdgeList* newEdgeList(Edge* edge, EdgeList* next){
  EdgeList* edge_list = (EdgeList*)malloc(sizeof(EdgeList));
  edge_list->edge = edge;
  edge_list->next = next;
  return edge_list;
}

/* Returns a newly created Vertex with ID 'id', value 'value', and adjacency
 * list 'adjList'.
 * Precondition: 'id' is valid for this vertex
 */
Vertex* newVertex(int id, void* value, EdgeList* adjList){
  if(id < 0) return NULL;

  Vertex* vertex = (Vertex*)malloc(sizeof(Vertex));
  vertex->id = id;
  vertex->value = value;
  vertex->adjList = adjList;
  return vertex;
}

/* Returns a newly created Graph with space for 'numVertices' vertices.
 * Precondition: numVertices >= 0
 */
Graph* newGraph(int numVertices){
  if(numVertices < 0){
    return NULL;
  }
  Graph* graph = (Graph*)malloc(sizeof(Graph));
  graph->numVertices = numVertices;
  graph->numEdges = 0;
  graph->vertices = (Vertex**)malloc(numVertices * sizeof(Vertex*));

  for(int i = 0; i < numVertices; i++){
     graph->vertices[i] = (Vertex*)malloc(sizeof(Vertex));

     graph->vertices[i]->id = i;
     graph->vertices[i]->value = NULL;
     graph->vertices[i]->adjList = NULL;
  }

  return graph;
}

/* Frees memory allocated for EdgeList starting at 'head'.
 */
void deleteEdgeList(EdgeList* head){
  EdgeList* current_node = head;
  EdgeList* next_node = NULL;
  while(current_node != NULL){
    next_node = current_node->next;
    free(current_node->edge);
    free(current_node);
    current_node = next_node;
  }

}

/* Frees memory allocated for 'vertex' including its adjacency list.
 */
void deleteVertex(Vertex* vertex){
  if(vertex == NULL) return;
  deleteEdgeList(vertex->adjList);
  free(vertex);
}

/* Frees memory allocated for 'graph'.
 */
void deleteGraph(Graph* graph){
  if(graph == NULL) return;
  for(int i = 0; i < graph->numVertices; i++){
    deleteVertex(graph->vertices[i]);
  }
  free(graph->vertices);
  free(graph);
}