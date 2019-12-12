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
node* ordered_add(node *head, int item);
node* scanf_list(node *head, int n);
int compare_list(int quant, node *head1, node *head2);

int main()
{
    int n;

    node* list1 = create_linked_list();
    node* list2 = create_linked_list();

    scanf("%d", &n);
    list1 = scanf_list(list1, n);
    scanf("%d", &n);
    list2 = scanf_list(list2, n);

    int value = compare_list(0, list1, list2);

    if(value < n)
    {
        printf("0");
    }
    else{
        printf("1");
    }
}

node* create_linked_list()
{
	return NULL;
}

node* add(int item)
{
	node *new_node = (node*) malloc(sizeof(node));
	new_node->item = item;
	new_node->next = NULL;
	return new_node;
}

node* ordered_add(node *head, int item) // adaptado da fun??o remove
{
	node *new_node = add(item);

	node *previous = NULL;
	node *current = head;

	if (head == NULL)
	{
		return new_node;
	}
	if (head->item >= item)
	{
		new_node->next = head;
		return new_node;
	}

	while (current != NULL && (current->item <= item))
	{
		previous = current;
		current = current->next;
	}

	if (previous->next != NULL)
	{
		previous->next = new_node;
		new_node->next = current;
	}
	else{
		previous->next = new_node;
		new_node->next = NULL;
	}

	return head;
}

node* scanf_list(node *head, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        int item;
        scanf("%d", &item);
        head = ordered_add(head, item);
    }
    return head;
}

int compare_list(int quant, node *head1, node *head2)
{
	node *head1_aux = head1;

	if (head2 == NULL)
	{
		return quant;
	}

	while ((head2->item) >= (head1_aux->item))
	{
		if ((head2->item) == (head1_aux->item))
		{
			quant+=1;
		}
		if (head1_aux->next == NULL)
		{
			return quant;
		}
		head1_aux = head1_aux->next;
	}

	compare_list(quant, (head1 = head1->next), (head2 = head2->next));
}
