#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

struct node{
    int item;
    node *next;
    node *previous
};

node* create_doubly_linked_list();
int is_empty(node *head);
node* add(int item);
node* ordered_add(node *head, int item);
node* end_add(node *head, int item);
node* begin_add(node *head, int item);
node* node_remove(node *head, int item);
node* node_search(node *head, int item);
void print_doubly_linked_list(node *head);

int main()
{
    node *head = create_doubly_linked_list();

    head = begin_add(head, 15);
	head = end_add(head, 7);
	head = ordered_add(head, 11);
	//head = node_remove(head, 7);
	print_doubly_linked_list(head);

	return 0;
}

node* create_doubly_linked_list()
{
	return NULL;
}

int is_empty(node *head)
{
    return (head == NULL);
}

node* add(int item)
{
	node *new_node = (node*) malloc(sizeof(node));
	new_node->item = item;
	new_node->next = NULL;
	new_node->previous = NULL;
	return new_node;
}

node* ordered_add(node *head, int item)
{
    node *new_node = add(item);
    node *previous = NULL;
    node *current = head;

    if(is_empty(head))
    {
        return new_node;
    }
    else if(head->item >= item)
    {
        new_node->next = head;
        head->previous = new_node;
        return new_node;
    }

    while(current != NULL && (current->item < item))
    {
        previous = current;
        current = current->next;
    }

    if(previous->next != NULL)
    {
        previous->next = new_node;
        new_node->next = current;
        new_node->previous = previous;
    }
    else{
        previous->next = new_node;
        new_node->previous = previous;
    }

    return head;
}

node* end_add(node *head, int item)
{
	node *new_node = add(item);
	node *aux = head;

	if (is_empty(head))
	{
		return new_node;
	}

	while (aux->next != NULL)
	{
		aux = aux->next;
	}

	aux->next = new_node;
    new_node->previous = aux;
	return head;
}

node* begin_add(node *head, int item)
{
	node *new_node = add(item);
	if (!is_empty(head))
    {
		new_node->next = head;
		head->previous = new_node;
	}
	return new_node;
}

node* node_remove(node *head, int item)
{
    node *previous = NULL;
	node *current = head;

	if (current != NULL && current->item == item) // se o item que deve ser removido for a cabeça
	{
		head = current->next;
		current->next = NULL;
		free(current);
		return head;
	}

	while (current != NULL) // se o item que deve ser removido não for a cabeça
	{
		if (current->item == item)
		{
			previous->next = current->next;
			free(current); // libera o node atual da memoria
			return head;
		}
		previous = current; // incrementa o anterior
		current = current->next; // incrementa o atual
	}

	return head;
}

node* node_search(node *head, int item)
{
	if (head != NULL)
	{
		if (head->item == item)
		{
			return head;
		}
		return node_search(head->next, item);
	}
	return NULL;
}

void print_doubly_linked_list(node *head)
{
	if (head == NULL)
	{
		return;
	}
	printf("%d\n", head->item);
	print_doubly_linked_list(head->next);
}
