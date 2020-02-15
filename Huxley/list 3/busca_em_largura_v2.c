#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NODE node;
typedef struct QUEUE queue;
typedef struct ADJLIST adj_list;
typedef struct GRAPH graph;

struct NODE
{
    int item;
    node *next;
};

struct QUEUE
{
    node *end;
    node *begin;
};

struct ADJLIST
{
    int item;
    adj_list *next;
};

struct GRAPH
{
    int size;
    int *dist;
    int *prev;
    adj_list **vertices;
    bool *visited;
};

node* create_node(int item);
queue* create_queue();
bool is_empty(queue *queue);
void enqueue(queue *queue, int item);
void dequeue(queue *queue);

graph* create_graph(int size);
adj_list* create_adj_list(int item);
void add_edge(graph *new_graph, int vertex1, int vertex2);
void bfs(graph *new_graph, int source);
void graph_path(graph *new_graph, int source, int destiny);
void way_print(graph *new_graph);

int main()
{
    int vertices, edges, tests, i, j;
    scanf("%d %d %d", &vertices, &edges, &tests);
    graph *new_graph = create_graph(vertices);

    int vertex1, vertex2;
    for(i = 0; i < edges; i++)
    {
        scanf("%d %d", &vertex1, &vertex2);
        add_edge(new_graph, vertex1, vertex2);
    }
    for(i = 1; i <= tests; i++)
    {
        printf("--------\n\n");
        scanf("%d %d", &vertex1, &vertex2);
        printf("Caso de Teste #%d - BFS(%d)\n\n", i, vertex1);

        bfs(new_graph, vertex1);

        for(j = 0; j < new_graph->size; j++)
        {
            int aux = j, dist = 0;
            while(aux != vertex1)
            {
                aux = new_graph->prev[aux];
                if(aux == j)
                {
                    dist = -1;
                    break;
                }
                dist += 1;
            }
            new_graph->dist[j] = dist;
        }

        way_print(new_graph);
        graph_path(new_graph, vertex1, vertex2);
    }
    printf("--------\n\n");
    free(new_graph);
}

node* create_node(int item)
{
    node *new_node = (node*) malloc(sizeof(node));
    new_node->item = item;
    new_node->next = NULL;
    return new_node;
}

queue* create_queue()
{
    queue *new_queue = (queue*) malloc(sizeof(queue));
    new_queue->begin = NULL;
    new_queue->end = NULL;
    return new_queue;
}

bool is_empty(queue *queue)
{
    return(queue->begin == NULL);
}

void enqueue(queue *queue, int item)
{
    node *new_node = create_node(item);
    if(!is_empty(queue))
    {
        queue->end->next = new_node;
        queue->end = new_node;
    }
    else{
        queue->begin = new_node;
        queue->end = new_node;
    }
}

void dequeue(queue *queue)
{
    if(is_empty(queue))
    {
        return;
    }
    node *aux = queue->begin;
    queue->begin = queue->begin->next;
    free(aux);
}

graph* create_graph(int size)
{
    graph *new_graph = (graph*) malloc(sizeof(graph));
    new_graph->size = size;

    new_graph->dist = (int*) malloc(sizeof(int) * size);
    new_graph->prev = (int*) malloc(sizeof(int) * size);
    new_graph->vertices = (adj_list**) malloc(sizeof(adj_list*) * size);
    new_graph->visited = (bool*) malloc(sizeof(bool) * size);

    int i;
    for(i = 0; i < size; i++)
    {
        new_graph->dist[i] = -1;
        new_graph->prev[i] = i;
        new_graph->vertices[i] = NULL;
        new_graph->visited[i] = false;
    }
    return new_graph;
}

adj_list* create_adj_list(int item)
{
    adj_list *adj = (adj_list*) malloc(sizeof(adj_list));
    adj->item = item;
    adj->next = NULL;
    return adj;
}

void add_edge(graph *new_graph, int vertex1, int vertex2)
{
    adj_list *adj = create_adj_list(vertex2);
    adj->next = new_graph->vertices[vertex1];
    new_graph->vertices[vertex1] = adj;
}

void bfs(graph *new_graph, int source)
{
    int i, j, aux;
    for(i = 0; i < new_graph->size; i++)
    {
        new_graph->dist[i] = -1;
        new_graph->prev[i] = i;
        new_graph->visited[i] = false;
    }

    queue *queue = create_queue();
    adj_list *current = new_graph->vertices[source];
    new_graph->visited[source] = true;
    new_graph->prev[source] = source;
    enqueue(queue, source);

    while(!is_empty(queue))
    {
        aux = queue->begin->item;
        dequeue(queue);
        printf("Iniciando busca em largura a partir de %d\n", aux);
        current = new_graph->vertices[aux];
        int sorted[new_graph->size], next = 0;

        while(current != NULL)
        {
            if(!new_graph->visited[current->item])
            {
                new_graph->visited[current->item] = true;
                new_graph->prev[current->item] = aux;
                sorted[next++] = current->item;
            }
            current = current->next;
        }
        for(i = 0; i < next; i++)
        {
            for(j = i+1; j < next; j++)
            {
                if(sorted[i] > sorted[j])
                {
                    int aux = sorted[i];
                    sorted[i] = sorted[j];
                    sorted[j] = aux;
                }
            }
        }
        for(i = 0; i < next; i++)
        {
            enqueue(queue, sorted[i]);
        }
    }

    while(!is_empty(queue))
    {
        dequeue(queue);
    }
    free(queue);
    printf("\n");
}

void graph_path(graph *new_graph, int source, int destiny)
{
    if (new_graph->dist[destiny] == -1)
    {
        printf("Sem caminho entre %d e %d\n", source, destiny);
    }
    else{
        printf("Caminho entre %d e %d:", source, destiny);
        int path[new_graph->dist[destiny]];
        int aux_dest = destiny;

        int i = 0, j;
        while (aux_dest != source)
        {
            path[i++] = aux_dest;
            aux_dest = new_graph->prev[aux_dest];
        }
        path[i++] = aux_dest;

        for (j = i-1; j > 0; j--)
        printf(" %d =>", path[j]);
        printf(" %d\n", path[j]);
    }
    printf("\n");
}

void way_print(graph *new_graph)
{
    int i;
    if(new_graph == NULL)
    {
        return;
    }
    for(i = 0; i < new_graph->size; i++)
    {
        printf("%d | ", i);
        if(new_graph->dist[i] == -1)
        {
            printf("- | ");
        }
        else{
            printf("%d | ", new_graph->dist[i]);
        }
        if(new_graph->prev[i] == i)
        {
            printf("-\n");
        }
        else{
            printf("%d\n", new_graph->prev[i]);
        }
    }
    printf("\n");
}
