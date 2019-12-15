#include <stdio.h>
#include <stdlib.h>

#define maxQueue 100
#define max 100

typedef struct Adj Adj;
typedef struct Graph Graph;
typedef struct Queue Queue;

struct Adj
{
    int item;
    Adj *next;
};

struct Graph
{
    Adj *vertices[max];
    short visited[max];
};

struct Queue
{
    int current_size, head, tail;
    int items[maxQueue];
};

Queue* create_queue();
int is_empty(Queue *queue);
void enqueue(Queue *queue, int item);
int dequeue(Queue *queue);
Graph* create_graph();
Adj* create_adj_list(int item);
void add_edge(Graph *graph, int vertex1, int vertex2);
void bfs(Graph *graph, int source);

int main()
{
    Graph *graph = create_graph();
    add_edge(graph, 1, 1);
    add_edge(graph, 1, 2);
    add_edge(graph, 2, 3);
    add_edge(graph, 2, 4);
    add_edge(graph, 3, 5);
    bfs(graph, 1);
}

Queue* create_queue()
{
    Queue *new_queue = (Queue *) malloc(sizeof(Queue));
    new_queue->current_size = 0;
    new_queue->head = 0;
    new_queue->tail = maxQueue - 1;
    return new_queue;
}

int is_empty(Queue *queue)
{
    return (queue->current_size == 0);
}

void enqueue(Queue *queue, int item)
{
    queue->tail = (queue -> tail + 1) % maxQueue;
    queue->items[queue->tail] = item;
    ++queue->current_size;
}

int dequeue(Queue *queue)
{
    int dequeued = queue -> items[queue -> head];
    queue->head = (queue -> head + 1) % maxQueue;
    --queue->current_size;
    return dequeued;
}

Graph* create_graph()
{
    Graph *graph = (Graph *) malloc(sizeof(Graph));
    int i;
    for(i = 1; i <= max; i++)
    {
        graph -> vertices[i] = NULL;
        graph -> visited[i] = 0;
    }
    return graph;
}

Adj* create_adj_list(int item)
{
    Adj *new_adj = (Adj*) malloc(sizeof(Adj));
    new_adj->item = item;
    new_adj->next = NULL;
    return new_adj;
}

void add_edge(Graph *graph, int vertex1, int vertex2)
{
    Adj *vertex = create_adj_list(vertex2);
    vertex -> next = graph -> vertices[vertex1];
    graph -> vertices[vertex1] = vertex;
}

void bfs(Graph *graph, int source)
{
    Queue *queue = create_queue();
    int dequeued;
    Adj *adj_list = graph->vertices[source];
    graph->visited[source] = 1;
    printf("%d\n", source);
    enqueue(queue, source);
    while(!is_empty(queue))
    {
        dequeued = dequeue(queue);
        adj_list = graph->vertices[dequeued];

    while(adj_list != NULL)
    {
        if(!graph->visited[adj_list -> item])
        {
            printf("%d\n", adj_list -> item);
            graph->visited[adj_list -> item] = 1;
            enqueue(queue, adj_list -> item);
        }
        adj_list = adj_list -> next;
    }
  }
}
