#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

struct node
{
	int item;
	node *next;
};

node* create_linked_list();
node* add(int item);
node* end_add(node *head, int item);
node* reverse_list(node *head);
void print_linked_list(node *head);

int main()
{
	node *list = create_linked_list();

    int item;
    while (scanf("%d", &item) != EOF)
    {
        list = end_add(list, item);
    }

    list = reverse_list(list);

    print_linked_list(list);

    return 0;
}

node* create_linked_list()
{
    return NULL;
}

node* add(int item)
{
	node *head = (node*) malloc(sizeof(node));
	head->item = item;
	head->next = NULL;
	return head;
}

node* end_add(node *head, int item)
{
	node *new_node = add(item);
	node *aux = head;

	if (head == NULL)
	{
		return new_node;
	}

	while (aux->next != NULL)
	{
		aux = aux->next;
	}

	aux->next = new_node;
	return head;
}

node* reverse_list(node *head)
{
    node *current = head;
    node *previous = NULL;
    node *next;

    while (current != NULL)
    {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }

    head = previous;

    return head;
}

void print_linked_list(node *head)
{
	if (head == NULL)
	{
		return;
	}
	printf("%d ", head->item);
	print_linked_list(head->next);
}
