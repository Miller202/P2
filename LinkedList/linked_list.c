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
node* begin_add(node *head, int item);
node* node_remove(node *head, int item);
int node_search(node *head, int item);
void print_linked_list(node *head);

int main()
{
	node *head = create_linked_list();
	head = begin_add(head, 5);
	head = begin_add(head, 8);
	head = end_add(head, 11);
	head = end_add(head, 14);
	print_linked_list(head);
	head = node_remove(head, 8);
	head = node_remove(head, 14);
	print_linked_list(head);

	if(node_search(head, 5))
    {
		printf("have 5\n");
	}
	else{
		printf("don't have 5\n");
	}
	if(node_search(head, 10))
    {
		printf("have 10\n");
	}
	else{
		printf("don't have 10\n");
	}
	return 0;
}

node* create_linked_list()
{
    return NULL;
}

node* add(int item) // cria um node
{
	node *head = (node*) malloc(sizeof(node)); // aloca memoria
	head->item = item; // adiciona o valor ao node
	head->next = NULL; // next do node aponta para NULL
	return head; // retorna a cabeça
}

node* end_add(node *head, int item) // insere no final
{
	node *new_node = add(item); // cria o new_node
	node *aux = head; // aux aponta para head para nao perder o ponteiro da cabeça

	if (head == NULL) // quando a lista for nula, retorna o new_node
	{
		return new_node;
	}

	while (aux->next != NULL) // enquanto nao for o ultimo item, chama o proximo
	{
		aux = aux->next;
	}

	aux->next = new_node;
	return head;
}

node* begin_add(node *head, int item) // insere no inicio
{
	node *new_node = add(item); // cria o new_node
	new_node->next = head; // faz o new node apontar para a cabeça
	return new_node;
}

node* node_remove(node *head, int item) // remove um node de uma lista
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


void print_linked_list(node *head) // imprime a lista
{
	if (head == NULL) // imprimir enquanto a lista nao acabar
	{
		return;
	}
	printf("%d\n", head->item);
	print_linked_list(head->next); // recursao para chamar o proximo head
}

int node_search(node *head, int item) // procurar um item na lista
{
	if (head != NULL)
	{
		if (head->item == item)
		{
			return 1; // item encontrado
		}
		return node_search(head->next, item); // chama o proximo
	}
	return 0; // item nao encontrado
}
