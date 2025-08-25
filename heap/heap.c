#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ROOT_INDEX 1
#define NOTHING -1

typedef struct heap_node {
  int priority;  // priority of this node
  int id;        // the unique ID of this node; 0 <= id < size
} HeapNode;


typedef struct min_heap {
  int size;       // the number of nodes in this heap; 0 <= size <= capacity
  int capacity;   // the number of nodes that can be stored in this heap
  HeapNode* arr;  // the array that stores the nodes of this heap
  int* indexMap;  // indexMap[id] is the index of node with ID id in array arr
} MinHeap;



/* Swaps contents of heap->arr[index1] and heap->arr[index2] if both 'index1'
 * and 'index2' are valid indices for minheap 'heap'. Has no effect
 * otherwise.
 */
void swap(MinHeap* heap, int index1, int index2){
       if(heap != NULL){
       int size = heap->size;
       if((index1 > 0 && index2 > 0) && (index1 <= size && index2 <= size)&&(index1 != index2)){
              HeapNode tmp = heap->arr[index1];//tmp is the HeapNode at old index1 position in array
              heap->arr[index1] = heap->arr[index2];
              heap->arr[index2] = tmp;

              heap->indexMap[heap->arr[index1].id] = index1;
              heap->indexMap[heap->arr[index2].id] = index2;
       }
    }
}

/* Bubbles up the element newly inserted into minheap 'heap' at index
 * 'nodeIndex', if 'nodeIndex' is a valid index for heap. Has no effect
 * otherwise.
 */
void bubbleUp(MinHeap* heap, int nodeIndex){
       if(heap != NULL){
              if(nodeIndex >= 1 && nodeIndex <= heap->size){
                     int parentIndex = nodeIndex / 2;
                     while (nodeIndex > 1 && heap->arr[nodeIndex].priority < heap->arr[parentIndex].priority) {
                            swap(heap, nodeIndex, parentIndex);
                            nodeIndex = parentIndex;
                            parentIndex = nodeIndex / 2;
                     }
              }
       }
}

/* Bubbles down the element newly inserted into minheap 'heap' at the root,
 * if it exists. Has no effect otherwise.
 */
void bubbleDown(MinHeap* heap){
       int index = 1;
       while (true) {
              int left = 2 * index;
              int right = 2 * index + 1;
              int smallest = index;

        if (left <= heap->size && heap->arr[left].priority < heap->arr[smallest].priority) {
              //check if left subnode is smaller
              smallest = left;
        }    
        if (right <= heap->size && heap->arr[right].priority < heap->arr[smallest].priority) {
              //check if right subnode is smaller
              smallest = right;
        }

        //right now smallest is the index of the smaller left/right node index
        
        if (smallest == index) {
              break;
        }

       
        swap(heap, index, smallest);

        
        index = smallest;
    }
}

/* Returns the index of the left child of a node at index 'nodeIndex' in
 * minheap 'heap', if such exists.  Returns NOTHING if there is no such left
 * child.
 */
int leftIdx(MinHeap* heap, int nodeIndex){
       int left = 2 * nodeIndex;
       if(left >= 1 && left <= heap->size){
              return left;
       }
       return NOTHING;
}

/* Returns the index of the right child of a node at index 'nodeIndex' in
 * minheap 'heap', if such exists.  Returns NOTHING if there is no such right
 * child.
 */
int rightIdx(MinHeap* heap, int nodeIndex){
       int right = 2 * nodeIndex + 1;
       if(right >= 1 && right <= heap->size){
              return right;
       }
       return NOTHING;
}

/* Returns the index of the parent of a node at index 'nodeIndex' in minheap
 * 'heap', if such exists.  Returns NOTHING if there is no such parent.
 */
int parentIdx(MinHeap* heap, int nodeIndex){
       int parent = nodeIndex / 2;
       if(parent >= 0 && parent <= heap->size){
              return parent;
       }
       return NOTHING;
}

/* Returns True if 'maybeIdx' is a valid index in minheap 'heap', and 'heap'
 * stores an element at that index. Returns False otherwise.
 */
bool isValidIndex(MinHeap* heap, int maybeIdx){
       if(heap == NULL) return false;
       return (maybeIdx >= 1 && maybeIdx <= heap->size);
}

/* Returns node at index 'nodeIndex' in minheap 'heap'.
 * Precondition: 'nodeIndex' is a valid index in 'heap'
 *               'heap' is non-empty
 */
HeapNode nodeAt(MinHeap* heap, int nodeIndex){
       return heap->arr[nodeIndex];
}

/* Returns priority of node at index 'nodeIndex' in minheap 'heap'.
 * Precondition: 'nodeIndex' is a valid index in 'heap'
 *               'heap' is non-empty
 */
int priorityAt(MinHeap* heap, int nodeIndex){
       return heap->arr[nodeIndex].priority;
}

/* Returns ID of node at index 'nodeIndex' in minheap 'heap'.
 * Precondition: 'nodeIndex' is a valid index in 'heap'
 *               'heap' is non-empty
 */
int idAt(MinHeap* heap, int nodeIndex){
       return heap->arr[nodeIndex].id;
}

/* Returns index of node with ID 'id' in minheap 'heap'.
 * Precondition: 'id' is a valid ID in 'heap'
 *               'heap' is non-empty
 */
int indexOf(MinHeap* heap, int id){
       return heap->indexMap[id];
}



/* Returns the node with minimum priority in minheap 'heap'.
 * Precondition: heap is non-empty
 */
HeapNode getMin(MinHeap* heap){
       return heap->arr[ROOT_INDEX];
}

/* Removes and returns the node with minimum priority in minheap 'heap'.
 * Precondition: heap is non-empty
 */
HeapNode extractMin(MinHeap* heap){
       HeapNode minPriority = getMin(heap);
       heap->arr[ROOT_INDEX] = heap->arr[heap->size];//copy the "last" heap node into root
       heap->indexMap[heap->arr[ROOT_INDEX].id] = ROOT_INDEX;//update the index of "last" heap node as ROOT_INDEX
       heap->size --;

       heap->arr[heap->size + 1].id = 0;
       heap->arr[heap->size + 1].priority = 0;
       heap->indexMap[minPriority.id] = NOTHING;//delete the minPriority node's information in indexMap
       if(heap->size >= 1){
              bubbleDown(heap);
       }
       return minPriority;
}

/* Inserts a new node with priority 'priority' and ID 'id' into minheap 'heap'.
 * Precondition: 'id' is unique within this minheap
 *               0 <= 'id' < heap->capacity
 *               heap->size < heap->capacity
 */
void insert(MinHeap* heap, int priority, int id){
       if(heap->size + 1 <= heap->capacity){
              heap->size ++;
              heap->arr[heap->size].priority = priority;
              heap->arr[heap->size].id = id;
              heap->indexMap[id] = heap->size;
              bubbleUp(heap, heap->size);
       }
}

/* Returns priority of the node with ID 'id' in 'heap'.
 * Precondition: 'id' is a valid node ID in 'heap'.
 */
int getPriority(MinHeap* heap, int id){
       return heap->arr[heap->indexMap[id]].priority;
}

/* Sets priority of node with ID 'id' in minheap 'heap' to 'newPriority', if
 * such a node exists in 'heap' and its priority is larger than
 * 'newPriority', and returns True. Has no effect and returns False, otherwise.
 * Note: this function bubbles up the node until the heap property is restored.
 */
bool decreasePriority(MinHeap* heap, int id, int newPriority) {
    int nodeIndex = indexOf(heap, id);
    if (isValidIndex(heap, nodeIndex) && heap->arr[nodeIndex].priority > newPriority) {
        heap->arr[nodeIndex].priority = newPriority; // 更新优先级
        bubbleUp(heap, nodeIndex); // 根据新优先级上浮节点
        return true;
    }
    return false;
}




/* Returns a newly created empty minheap with initial capacity 'capacity'.
 * Precondition: capacity >= 0
 */
MinHeap* newHeap(int capacity){
       if(capacity >= 0){
              MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
              heap->size = 0;
              heap->capacity = capacity;

              heap->arr = (HeapNode*)malloc(sizeof(HeapNode) * (capacity + 1));//[0, 1, 2, .... capacity-1, capacity] in total capacity+1 # of space
              heap->indexMap = (int*)malloc(sizeof(int) * (capacity + 1));
              for(int i = 0; i < capacity + 1; i ++){
                     heap->indexMap[i] = NOTHING;
                     heap->arr[i].id = 0;
                     heap->arr[i].priority = 0;
              }
              return heap;
       }
       return NULL;
}

/* Frees all memory allocated for minheap 'heap'.
 */
void deleteHeap(MinHeap* heap){
       if(heap != NULL){
              //delete heap->arr[]
              if(heap->arr != NULL){
                     free(heap->arr);
                     heap->arr = NULL;
              }
              
              //delete heap->indexMap[]
              if(heap->indexMap != NULL){
                     free(heap->indexMap);
                     heap->indexMap = NULL;
              }
              free(heap);
              heap = NULL;
       }
}


void printHeap(MinHeap* heap) {
  printf("MinHeap with size: %d\n\tcapacity: %d\n\n", heap->size,
         heap->capacity);
  printf("index: priority [ID]\t ID: index\n");
  for (int i = 0; i < heap->capacity; i++)
    printf("%d: %d [%d]\t\t%d: %d\n", i, priorityAt(heap, i), idAt(heap, i), i,
           indexOf(heap, i));
  printf("%d: %d [%d]\t\t\n", heap->capacity, priorityAt(heap, heap->capacity),
         idAt(heap, heap->capacity));
  printf("\n\n");
}





int main(){
    int heap_capacity;
    printf("please input the capacity of the min_heap:\n");
    scanf("%d",&heap_capacity);

    MinHeap* heap = newHeap(heap_capacity);

    if (!heap) {
        printf("Failed to create a min heap.\n");
        return 1;
    }

    printf("Heap created, with capacity: %d\n", heap_capacity);

    int choice, priority, id;
    HeapNode minNode;

    choice = -1;
    while (choice != 4) {
        printf("\nOptions:\n");
        printf("1 - Insert a new node\n");
        printf("2 - Extract the minimum node\n");
        printf("3 - Print the heap\n");
        printf("4 - Delete the min heap and exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Insert a new node
                printf("Enter ID and priority of the new node:\n ");
                scanf("%d %d", &id, &priority);
                insert(heap, priority, id);
                break;
            case 2: // Extract the minimum node
                if (heap->size > 0) {
                    minNode = extractMin(heap);
                    printf("Extracted node: ID = %d, Priority = %d\n", minNode.id, minNode.priority);
                } else {
                    printf("The heap is empty.\n");
                }
                break;
            case 3: // Print the heap
                printHeap(heap);
                break;
            case 4: // Delete the min heap and exit
                deleteHeap(heap);
                printf("Min heap deleted. Exiting.\n");
                return 0;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    // Not reached, but included for completeness
    deleteHeap(heap);
    return 0;
}