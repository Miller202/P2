#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 20

typedef struct adj_list adj_list;
typedef struct graph graph;

struct adj_list
{
    int item;
    adj_list *next;
};

struct graph
{
    adj_list *vertices[MAX_SIZE];
    short visited[MAX_SIZE];
};

graph* create_graph();
adj_list* create_adj_list(int item);
void add_edge(graph *graph, int vertex1, int vertex2);
void dfs(graph *graph, int source);
//void bfs(graph *graph, int source);
void print_graph(graph *graph);

int main()
{
    graph *undirected_graph = create_graph();
    add_edge(undirected_graph, 1, 2);
}

graph* create_graph()
{
    graph *new_graph = (graph*) malloc(sizeof(graph));
    int i;
    for (i = 1; i < MAX_SIZE; i++)
    {
        new_graph->vertices[i] = NULL;
        new_graph->visited[i] = 0;
    }
    return new_graph;
}

adj_list* create_adj_list(int item)
{
    adj_list *new_adj_list = (adj_list*) malloc(sizeof(adj_list));
    new_adj_list->item = item;
    new_adj_list->next = NULL;
    return new_adj_list;
}

void add_edge(graph *graph, int vertex1, int vertex2)
{
    adj_list *vertex = create_adj_list(vertex2);
    vertex->next = graph->vertices[vertex1];
    graph->vertices[vertex1] = vertex;

    //Undirected graph. Edge to the other direction as well.
    vertex = create_adj_list(vertex1);
    vertex->next = graph->vertices[vertex2];
    graph->vertices[vertex2] = vertex;
}

void dfs(graph *graph, int source)
{
    graph->visited[source] = 1;
    printf("%d\n", source);

    adj_list *acess_list = graph->vertices[source];
    while (acess_list != NULL)
    {
        if (!graph->visited[acess_list->item])
        {
            dfs(graph, acess_list->item);
        }
        acess_list = acess_list->next;
    }
}

/*void bfs(graph *graph, int source)
{
    queue *queue = create_queue();
    int dequeued;
    adj_list * adj_list = graph->vertices[source];
    graph->visited[source] = 1;
    enqueue(queue, source);

    while (!is_empty(queue))
    {
        dequeued = dequeue(queue);
        adj_list = graph->vertices[dequeued];
        while (adj_list != NULL)
        {
            if (!graph->visited[adj_list->item])
            {
                printf("%d\n", adj_list->item);
                graph->visited[adj_list->item] = 1;
                enqueue(queue, adj_list->item);
            }
            adj_list = adj_list->next;
        }
    }
}*/
