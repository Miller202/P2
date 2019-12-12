#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

struct node{
    int item;
    node *next;
};

node* create_linked_list();
node* add(int item);
node* end_add(node *head, int item);
node* sort(node *head, int n);
void print_linked_list(node *head);

int main()
{
    node* list = create_linked_list();
    int n=0, item=0;

    while ((scanf("%d", &item)) != EOF)
    {
        list = end_add(list, item);
        n++;
    }
    while (n != 1)
    {
        list = sort(list, n);
        n--;
    }

    print_linked_list(list);
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

node* sort(node *head, int n)
{
    node* current;
    node* previous;
    node* aux;

    int i;
    for(i = 0; i < n; i++)
    {
        current = head;
        previous = NULL;
        int temp = 1;

        while(current->next != NULL)
        {
            aux = current->next;

            if((aux->item) < (current->item))
            {
                current->next = aux->next;
                aux->next = current;
                current = aux;

                if(previous != NULL)
                {
                    previous->next = aux;
                }
            }
            if(temp == 1)
            {
                head = current;
            }
            previous = current;
            current = current->next;
            temp = 0;
        }
    }
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
