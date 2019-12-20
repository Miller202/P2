#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

struct node {
	int item;
	node *next;
	node *previous;
};

typedef struct queue queue;

struct queue {
	int size;
	node *end;
	node *begin;
};

queue *create_queue();
node *node_add(int item);
void enqueue(queue *new_queue, int item);
void enqueue_priority(queue *new_queue, int item);
int dequeue(queue *new_queue);
void compare(queue *queue_1, queue *queue_2);

int main()
{
    int i, j, n, m, item;
    scanf("%d", &n);

    for(i = 0; i < n; i++)
    {
        queue *queue_1 = create_queue();
        queue *queue_2 = create_queue();

        scanf("%d", &m);
        for(j = 0; j < m; j++)
        {
            scanf("%d", &item);
            enqueue(queue_1, item);
            enqueue_priority(queue_2, item);
        }

        compare(queue_1, queue_2);
    }
}

node *node_add(int item)
{
	node *new_node = (node*) malloc(sizeof(node));
	new_node->item = item;
	new_node->next = NULL;
	new_node->previous = NULL;
	return new_node;
}

queue *create_queue()
{
	queue *new_queue = (queue*) malloc(sizeof(queue));
	new_queue->end = NULL;
	new_queue->begin = NULL;
	return new_queue;
}

void enqueue(queue *new_queue, int item)
{
	node *new_node = node_add(item);
	new_queue->size += 1;

	if (new_queue->end == NULL)
    {
        new_queue->end = new_node;
		new_queue->begin = new_node;
	}
	else{
        new_queue->end->next = new_node;
		new_queue->end = new_node;
	}
}

void enqueue_priority(queue *new_queue, int item)
{
	node *new_node = node_add(item);
	new_queue->size += 1;

	if(new_queue->begin != NULL)
    {
        node *temp = new_queue->begin;
		node *prev;

		while(temp != NULL && temp->item >= item)
        {
			temp = temp->next;
		}

		if(temp == NULL)
        {
			new_queue->end->next = new_node;
			new_node->previous = new_queue->end;
			new_queue->end = new_node;
		}
        else if(temp->previous == NULL)
        {
			new_queue->begin->previous = new_node;
			new_node->next = new_queue->begin;
			new_queue->begin = new_node;
		}
		else{
			prev = temp->previous;
			prev->next = new_node;
			new_node->previous = prev;
			new_node->next = temp;
			temp->previous = new_node;
		}
	}
	else{
		new_queue->begin = new_node;
		new_queue->end = new_node;
	}
}

int dequeue(queue *new_queue)
{
	new_queue->size -= 1;
	int item;

	if (new_queue->end == NULL)
    {
		printf("Fila Vazia\n");
		return -1;
	}
	else if (new_queue->begin == new_queue->end)
    {
		node *new_node = new_queue->begin;
		item = new_node->item;
		new_queue->begin = new_queue->end = NULL;
		return item;
	}
	else {
		node *new_node = new_queue->begin;
		item = new_node->item;
		new_queue->begin = new_queue->begin->next;
		return item;
	}
}

void compare(queue *queue_1, queue *queue_2)
{
    int cont = 0;
    while ((queue_1->begin != NULL) && (queue_2->begin != NULL))
    {
        if (queue_1->begin->item == queue_2->begin->item)
        {
            cont++;
        }

        queue_1->begin = queue_1->begin->next;
        queue_2->begin = queue_2->begin->next;
    }

    printf("%d\n", cont);
}
