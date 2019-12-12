#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

struct node
{
    int item;
    node *next;
};

node* create_linked_list();
void merge(int *array, int *aux, int begin1, int end1, int begin2, int end2);
void merge_sort(int *array, int *aux, int begin, int end);
node* add(int item);
node* ordered_add(node *head, int item);
void compare_list(int *quant, node *head1, node *head2);

int main()
{
	int i, quant=0;
	int list1[20], list2[20], aux[20];

	node* head1 = create_linked_list();
	node* head2 = create_linked_list();

	for (i = 0; i < 20; i++)
	{
		scanf("%d", &list1[i]);
	}
	merge_sort(list1, aux, 0, 19);

	for (i = 0; i < 20; i++)
	{
		scanf("%d", &list2[i]);
	}
    merge_sort(list2, aux, 0, 19);

	for (i = 0; i < 20; i++)
	{
		if (list1[i] != list1[i+1])
		{
			head1 = ordered_add(head1, list1[i]);
		}

		if (list2[i] != list2[i+1])
		{
			head2 = ordered_add(head2, list2[i]);
		}
	}
	compare_list(&quant, head1, head2);

	if (quant == 0)
	{
		printf("VAZIO");
	}

	return 0;
}

node* create_linked_list()
{
	return NULL;
}

void merge(int *array, int *aux, int begin1, int end1, int begin2, int end2)
{
    int i, temp=0;
    int left = begin1;
    int right = end2;

    while(begin1 <= end1 || begin2 <= end2)
    {
        if(begin1 > end1)
        {
            while(begin2 <= end2)
            {
                aux[temp] = array[begin2];
                temp++;
                begin2++;
            }
        }
        else if(begin2 > end2)
        {
            while(begin1 <= end1)
            {
                aux[temp] = array[begin1];
                temp++;
                begin1++;
            }
        }
        else{
            if(array[begin1] < array[begin2])
            {
                aux[temp] = array[begin1];
                temp++;
                begin1++;
            }
            else{
                aux[temp] = array[begin2];
                temp++;
                begin2++;
            }
        }
    }

    temp = 0;
    for(i = left; i <= right; i++, temp++)
    {
        array[i] = aux[temp];
    }
}

void merge_sort(int *array, int *aux, int begin, int end)
{
    if (begin == end)
    {
        return 0;
    }

    int mid = (begin + end)/2;

    merge_sort(array, aux, begin, mid);
    merge_sort(array, aux, mid+1, end);

    merge(array, aux, begin, mid, mid+1, end);
}

node* add(int item)
{
	node *new_node = (node*) malloc(sizeof(node));
	new_node->item = item;
	new_node->next = NULL;
	return new_node;
}

node* ordered_add(node *head, int item) // adaptado da função remove
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

void compare_list(int *quant, node *head1, node *head2)
{
	node *head1_aux = head1;

	if (head2 == NULL)
	{
		return 0;
	}

	while ((head2->item) >= (head1_aux->item))
	{
		if ((head2->item) == (head1_aux->item))
		{
			printf("%d\n", head1_aux->item);
			*quant+=1;
		}
		if (head1_aux->next == NULL)
		{
			return 0;
		}
		head1_aux = head1_aux->next;
	}

	compare_list(quant, (head1 = head1->next), (head2 = head2->next));
}
