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
node* begin_add(node *head, int item);
void print_linked_list(node *head);

int main()
{
	node *list = create_linked_list();

    int item;

    while (scanf("%d", &item) != EOF)
    {
        list = begin_add(list, item);
    }

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

node* begin_add(node *head, int item)
{
	node *new_node = add(item);
	new_node->next = head;
	return new_node;
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
