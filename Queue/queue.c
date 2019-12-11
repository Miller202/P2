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
int is_empty(queue *new_queue);
void enqueue(queue *new_queue, int item);
int dequeue(queue *new_queue) ;
void enqueue_priority(queue *new_queue, int item);
void print_queue(queue *new_queue);

int main()
{
    queue *new_queue = create_queue();

	enqueue(new_queue, 3);
    enqueue(new_queue, 5);
	enqueue_priority(new_queue, 9);
	print_queue(new_queue);
	dequeue(new_queue);
	print_queue(new_queue);

    return 0;
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
	new_queue->end = new_queue->begin = NULL;
	return new_queue;
}

int is_empty(queue *new_queue)
{
	return (new_queue->end == NULL);
}

void enqueue(queue *new_queue, int item)
{
	node *new_node = node_add(item);
	new_queue->size += 1;

	if (is_empty(new_queue))
    {
		new_queue->begin = new_queue->end = new_node;
	}
	else{
        new_queue->end->next = new_node;
		new_queue->end = new_node;
	}
}

int dequeue(queue *new_queue)
{
	new_queue->size -= 1;
	int item;

	if (is_empty(new_queue))
    {
		printf("Empty Queue\n");
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

        if(temp->previous == NULL)
        {
			new_queue->begin->previous = new_node;
			new_node->next = new_queue->begin;
			new_queue->begin = new_node;
		}
		else if(temp == NULL)
        {
			new_queue->end->next = new_node;
			new_node->previous = new_queue->end;
			new_queue->end = new_node;
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
		new_queue->begin = new_queue->end = new_node;
	}
}

void print_queue(queue *new_queue)
{
    node *aux = new_queue->begin;
    while(aux != NULL)
    {
        printf("%d ", aux->item);
        aux = aux->next;
    }
    printf("\n");
}
