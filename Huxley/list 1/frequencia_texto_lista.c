#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node node;

struct node
{
    int frequencia;
    char caracter;
	node *next;
};

node* create_linked_list();
node* add(int frequencia, char caracter);
node* begin_add(node *head, int frequencia, char caracter);
void print_linked_list(node *head);

int main()
{
	char string[999];
	scanf("%[^\n]s", string);

	node* list = create_linked_list();

    int i, j;

	for(i = 0; i < 256; i++)
    {
        int n = strlen(string); //tamanho da string
        int f = 0;              // frequencia
        char c = ((char)(i));   // caractere

		for(j = 0; j < n; j++)
		{
		    f += (c == string[j]);
		}

		if(f)
		{
			list = begin_add(list, f, c);
		}
	}

	print_linked_list(list);
}

node* create_linked_list()
{
    return NULL;
}

node* add(int frequencia, char caracter)
{
	node *head = (node*) malloc(sizeof(node));
	head->frequencia = frequencia;
	head->caracter = caracter;
	head->next = NULL;
	return head;
}

node* begin_add(node *head, int frequencia, char caracter)
{
	node *new_node = add(frequencia, caracter);
	new_node->next = head;
	return new_node;
}

void print_linked_list(node *head)
{
	while(head != NULL)
    {
		printf("%c ", head->caracter);
        printf("%d\n", head->frequencia);
		head = head->next;
	}
}
