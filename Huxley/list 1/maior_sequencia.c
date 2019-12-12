#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node node;

struct node
{
	int item;
	node *next;
};

node* scan_strings();
node* create_linked_list();
node* add(int item);
node* end_add(node *head, int item);
void maior_sequencia(node *head, int begin, int end, int auxI, int auxF);

int main()
{
    scan_strings();
}

node* scan_strings()
{
    node *list = create_linked_list();

    char sequencia[99];
    scanf("%[^\n]s", sequencia);
    getchar();
    int n = strlen(sequencia);

    if ((n == 1) && (sequencia[0] == '0'))
    {
        return;
    }

    int i;
    for (i = 0; i < n; i++)
    {
        list = end_add(list, sequencia[i]);
    }

    maior_sequencia(list, 0, 0, 0, 0);

    scan_strings();
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

void maior_sequencia(node *head, int begin, int end, int auxI, int auxF)
{
    int inicio=0, fim=0;

    if (head == NULL)
    {
        printf("%d %d\n", begin, end);
        return;
    }

    while (head->item == '0')
    {
        inicio = auxI;
        fim = auxF;

        head = head->next;

        auxF++;

        if (head == NULL)
        {
            if ((fim-inicio) > (end-begin))
            {
                begin = inicio;
                end = fim;
            }
            printf("%d %d\n", begin, end);
            return;
        }
    }

    auxI = auxF;

    if ((fim-inicio) > (end-begin))
    {
        begin = inicio;
        end = fim;
    }

    maior_sequencia(head->next, begin, end, auxI+1, auxI+1);
}
