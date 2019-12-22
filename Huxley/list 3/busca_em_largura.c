#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
typedef struct Queue Queue;
typedef struct dist_node dist_node;
typedef struct adj_list adj_list;
typedef struct graph graph;

struct Node{
    int item;
    Node *previous;
    Node *next;
};

struct Queue{
    int size;
    Node *end;
    Node *begin;
};

struct dist_node{
    int predecessor;
    int dist;
};

struct adj_list{
    int node_quant;
    Node *Node;
};

struct graph{
    int vertices_quant;
    adj_list *vertices;
    int *visited;
};

Node* create_doubly_linked_list();
Node* node_add(int item);
Node* ordered_add(Node *head, int item);

Queue* queue_add();
int is_empty(Queue *new_queue);
void enqueue(Queue *new_queue, int item);
int dequeue(Queue *new_queue);

dist_node* create_array_dist(int vertices);
dist_node* add_array_dist(dist_node *array_dist, int key, int dist, int predecessor);
Node* create_adj_list(int item);
graph* create_graph(int size);
void edge_add(graph *new_graph, int vertex1, int vertex2);
void bfs(graph *new_graph, int source, dist_node *array_dist);
void way_print(dist_node *array_dist, int source, int end, int begin_end);

int main()
{
    int i, j, vertices, edge, test, vertex1, vertex2;

    scanf("%d %d %d", &vertices, &edge, &test);
    Node *new_array[edge];
    graph *new_graph = create_graph(vertices);
    dist_node *array_dist = create_array_dist(vertices);

    for (i = 0; i < edge; i++)
    {
        new_array[i] = NULL;
    }
    for(i = 0; i < edge; i++)
    {
        scanf("%d %d", &vertex1, &vertex2);
        new_array[vertex1] = ordered_add(new_array[vertex1], vertex2);
    }
    for (i = 0; i < edge; i++)
    {
        while (new_array[i] != NULL)
        {
            edge_add(new_graph, i, new_array[i]->item);
            new_array[i] = new_array[i]->next;
        }
    }
    for(j = 0; j < test; j++)
    {
        scanf("%d %d", &vertex1, &vertex2);
        printf("--------\n\nCaso de Teste #%d - BFS(%d)\n\n", j+1, vertex1);

        for (i = 0; i < vertices; i++)
        {
            new_graph->visited[i] = 0;
        }
        bfs(new_graph, vertex1, array_dist);

        for (i = 0; i < vertices; i++)
        {
            printf("%d | ", i);
            if (array_dist[i].dist != -100)
            {
                printf("%d", array_dist[i].dist);
            }
            else{
                printf("-");
            }
            printf(" | ");
            if (array_dist[i].predecessor != -1)
            {
                printf("%d", array_dist[i].predecessor);
            }
            else{
                printf("-");
            }
            printf("\n");
        }

        printf("\n");
        if (array_dist[vertex2].predecessor == -1)
        {
            printf("Sem caminho entre %d e %d\n", vertex1, vertex2);
        }
        else{
            way_print(array_dist, vertex1, vertex2, vertex2);
        }
        printf("\n");
    }
    printf("--------\n");
}

// Doubly Linked List
Node *create_doubly_linked_list()
{
    return NULL;
}

Node *node_add(int item)
{
    Node *new_Node = (Node*) malloc(sizeof(Node));
    new_Node->item = item;
    new_Node->previous = NULL;
    new_Node->next = NULL;
    return new_Node;
}

Node *ordered_add(Node *head, int item)
{
    Node *new_Node = node_add(item);
    Node *previous = NULL;
    Node *current = head;

    if (head == NULL)
    {
        return new_Node;
    }
    else if (head->item <= item)
    {
        new_Node->next = head;
        head->previous = new_Node;
        return new_Node;
    }
    while (current != NULL && current->item > item)
    {
        previous = current;
        current = current->next;
    }
    if (previous->next != NULL)
    {
        previous->next = new_Node;
        new_Node->next = current;
        new_Node->previous = previous;
    }
    else{
        previous->next = new_Node;
        new_Node->previous = previous;
    }
    return head;
}

// Queue
Queue *queue_add()
{
    Queue *new_queue = (Queue*) malloc(sizeof(Queue));
    new_queue->end = NULL;
    new_queue->begin = NULL;
    return new_queue;
}

int is_empty(Queue *new_queue)
{
    return (new_queue->end == NULL);
}

void enqueue(Queue *new_queue, int item)
{
    Node *new_Node = node_add(item);
    new_queue->size += 1;

    if (is_empty(new_queue))
    {
        new_queue->begin = new_queue->end = new_Node;
    }
    else{
        new_queue->end->next = new_Node;
        new_queue->end = new_Node;
    }
}

int dequeue(Queue *new_queue)
{
    new_queue->size -= 1;
    int item;

    if (is_empty(new_queue))
    {
        printf("Fila vazia\n");
        return -1;
    }
    else if (new_queue->begin == new_queue->end)
    {
        Node *new_Node = new_queue->begin;
        item = new_Node->item;
        new_queue->begin = new_queue->end = NULL;
        return item;
    }
    else{
        Node *new_Node = new_queue->begin;
        item = new_Node->item;
        new_queue->begin = new_queue->begin->next;
        return item;
    }
}

// graph

dist_node *create_array_dist(int vertices)
{
    dist_node *new_array = (dist_node*) malloc(sizeof(dist_node) * vertices);

    int i;
    for (i = 0; i < vertices; i++)
    {
        new_array[i].predecessor = -1;
        new_array[i].dist = -100;
    }
    return new_array;
}

dist_node *add_array_dist(dist_node *array_dist, int key, int dist, int predecessor)
{
    array_dist[key].predecessor = predecessor;
    array_dist[key].dist = dist;
    return array_dist;
}

Node* create_adj_list(int item)
{
    Node *new_adj_list = (Node*) malloc(sizeof(Node));
    new_adj_list->item = item;
    new_adj_list->previous = NULL;
    new_adj_list->next = NULL;
    return new_adj_list;
}

graph* create_graph(int size)
{
    graph *new_graph = (graph*) malloc(sizeof(graph));
    new_graph->vertices_quant = size;
    new_graph->vertices = (adj_list *)malloc(sizeof(adj_list) * (size));
    new_graph->visited = (int*) malloc(sizeof(int) * size);

    int i;
    for (i = 0; i < size; i++)
    {
        new_graph->vertices[i].Node = NULL;
        new_graph->vertices[i].node_quant = 0;
        new_graph->visited[i] = 0;
    }
    return new_graph;
}

void edge_add(graph *new_graph, int vertex1, int vertex2)
{
    Node *adj_list = create_adj_list(vertex2);
    adj_list->next = new_graph->vertices[vertex1].Node;
    new_graph->vertices[vertex1].Node = adj_list;
}

void bfs(graph *new_graph, int source, dist_node *array_dist)
{
    printf("Iniciando busca em largura a partir de %d\n", source);
    Queue *Queue = queue_add();
    enqueue(Queue, source);
    Node *adj_list = new_graph->vertices[source].Node;
    new_graph->visited[source] = 1;
    array_dist[source].predecessor = -1;
    array_dist[source].dist = 0;

    while (!is_empty(Queue))
    {
        int current_vertex = dequeue(Queue);
        adj_list = new_graph->vertices[current_vertex].Node;
        while (adj_list != NULL)
        {
            if (!new_graph->visited[adj_list->item])
            {
                array_dist[adj_list->item].dist = array_dist[current_vertex].dist + 1;
                printf("Iniciando busca em largura a partir de %d\n", adj_list->item);
                new_graph->visited[adj_list->item] = 1;
                enqueue(Queue, adj_list->item);
                array_dist = add_array_dist(array_dist, adj_list->item, array_dist[adj_list->item].dist, current_vertex);
            }
            adj_list = adj_list->next;
        }
    }
    printf("\n");
}

void way_print(dist_node *array_dist, int source, int end, int begin_end)
{
    if (array_dist[begin_end].predecessor == -1)
    {
        printf("Caminho entre %d e %d: ", begin_end, end);
        printf("%d => ", begin_end);
        return;
    }
    way_print(array_dist, begin_end, end, array_dist[begin_end].predecessor);

    if (begin_end == end)
    {
        printf("%d\n", begin_end);
    }
    else{
        printf("%d => ", begin_end);
    }
}
