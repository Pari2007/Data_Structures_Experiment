#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// Adjacency list node
typedef struct AdjListNode {
    int dest;
    struct AdjListNode* next;
} AdjListNode;

// Adjacency list
typedef struct AdjList {
    AdjListNode* head;
} AdjList;

// Graph structure
typedef struct Graph {
    int V;
    AdjList* array;
} Graph;

// Stack structure for topological sort
typedef struct Stack {
    int top;
    int items[MAX_VERTICES];
} Stack;

// Function to create a new adjacency list node
AdjListNode* createAdjListNode(int dest) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with V vertices
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->array = (AdjList*)malloc(V * sizeof(AdjList));
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;
    return graph;
}

// Function to add a directed edge from src to dest
void addEdge(Graph* graph, int src, int dest) {
    if (src < 0 || src >= graph->V || dest < 0 || dest >= graph->V) {
        printf("Invalid vertex index! Vertex indices must be between 0 and %d.\n", graph->V - 1);
        return;
    }
    // Add an edge from src to dest
    AdjListNode* newNode = createAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    printf("Added directed edge from %d to %d\n", src, dest);
}

// Stack operations
Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = -1;
    return stack;
}

int isFull(Stack* stack) {
    return stack->top == MAX_VERTICES - 1;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

void push(Stack* stack, int item) {
    if (isFull(stack)) return;
    stack->items[++stack->top] = item;
}

int pop(Stack* stack) {
    if (isEmpty(stack)) return -1;
    return stack->items[stack->top--];
}

// Recursive DFS helper function for Topological Sort
void topologicalSortUtil(Graph* graph, int v, int visited[], Stack* stack) {
    // Mark the current node as visited
    visited[v] = 1;

    // Recur for all the vertices adjacent to this vertex
    AdjListNode* pCrawl = graph->array[v].head;
    while (pCrawl != NULL) {
        int connectedVertex = pCrawl->dest;
        if (!visited[connectedVertex]) {
            topologicalSortUtil(graph, connectedVertex, visited, stack);
        }
        pCrawl = pCrawl->next;
    }

    // Push current vertex to stack which stores the result
    push(stack, v);
}

// Function to perform Topological Sort
void topologicalSort(Graph* graph) {
    Stack* stack = createStack();
    int visited[MAX_VERTICES] = {0};

    // Call the recursive helper function to store Topological Sort
    // starting from all vertices one by one
    for (int i = 0; i < graph->V; i++) {
        if (!visited[i]) {
            topologicalSortUtil(graph, i, visited, stack);
        }
    }

    // Print contents of the stack
    printf("\n--- Topological Sort Result (DFS) ---\n");
    while (!isEmpty(stack)) {
        printf("%d ", pop(stack));
    }
    printf("\n");

    free(stack);
}

// Function to display the graph's adjacency list
void displayGraph(Graph* graph) {
    printf("\n--- Graph Adjacency List ---\n");
    for (int v = 0; v < graph->V; ++v) {
        AdjListNode* pCrawl = graph->array[v].head;
        printf("Vertex %d: ", v);
        while (pCrawl) {
            printf("-> %d ", pCrawl->dest);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

// Main menu driver function
int main() {
    int V, choice, src, dest;

    printf("Enter the number of vertices in the graph: ");
    if (scanf("%d", &V) != 1 || V <= 0 || V > MAX_VERTICES) {
        printf("Invalid number of vertices!\n");
        return 1;
    }

    Graph* graph = createGraph(V);

    do {
        printf("\n=====================================\n");
        printf("     TOPOLOGICAL SORT (DFS) MENU     \n");
        printf("=====================================\n");
        printf("1. Add Directed Edge\n");
        printf("2. Display Adjacency List\n");
        printf("3. Perform Topological Sort\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter source vertex (0 to %d): ", V - 1);
                scanf("%d", &src);
                printf("Enter destination vertex (0 to %d): ", V - 1);
                scanf("%d", &dest);
                addEdge(graph, src, dest);
                break;
            case 2:
                displayGraph(graph);
                break;
            case 3:
                topologicalSort(graph);
                break;
            case 4:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
