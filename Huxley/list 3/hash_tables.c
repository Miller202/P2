#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
typedef struct hash_table hash_table;

struct node{
    int item;
    node *next;
    node *previous;
};

struct hash_table
{
    int quant;
    node *table[200];
};

node* create_linked_list();
node* add(int item);
node* end_add(node *head, int item);
int is_empty_list(node *head);
hash_table* create_hash_table(int size);
int is_empty_hash(hash_table *hash);
void put(hash_table *hash, int key, int item, int size);
void remove_hash(hash_table *hash, int key);
void print_hash_table(hash_table *hash, int key, int i, int j);

int main()
{
    int n, i, j;
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        int key, size;
        scanf("%d %d", &key, &size);
        hash_table *hash = create_hash_table(size);

        for (j = 0; j < size; j++)
        {
            int element;
            scanf("%d", &element);
            put(hash, key, element, size);
        }

        print_hash_table(hash, key, 0, 0);
        remove_hash(hash, key);
        printf("\n");
    }
}

node* create_linked_list()
{
    return NULL;
}

node* add(int item)
{
    node* new_node = (node*) malloc(sizeof(node));
    new_node->item = item;
    new_node->next = NULL;
    new_node->previous = NULL;
    return new_node;
}

node* end_add(node *head, int item)
{
    node *new_node = add(item);
	node *aux = head;

	if(is_empty_list(head))
	{
		return new_node;
	}

	while(aux->next != NULL)
	{
		aux = aux->next;
	}

	aux->next = new_node;
    new_node->previous = aux;
	return head;
}

int is_empty_list(node *head)
{
    return (head == NULL);
}

hash_table *create_hash_table(int size)
{
    hash_table *hash = (hash_table*) malloc(sizeof(hash_table));

    int i;
    for (i = 0; i < size; i++)
    {
        hash->table[i] = NULL;
    }

    return hash;
}

int is_empty_hash(hash_table *hash)
{
    return (hash == NULL);
}

void put(hash_table *hash, int key, int item, int size)
{
    int hkey = (item % key);

    if (is_empty_hash(hash) || hash->quant == size)
    {
        return;
    }
    if (hash->table[hkey] != NULL)
    {
        node *aux = hash->table[hkey];
        aux = end_add(aux, item);
        hash->quant += 1;
    }
    else{
        node *head = create_linked_list();
        head = end_add(head, item);
        hash->table[hkey] = head;
        hash->quant += 1;
    }
}

void remove_hash(hash_table *hash, int key)
{
    int i = 0;
    while (i < key)
    {
        if (hash->table[i] != NULL)
        {
            node *aux = hash->table[i];

            while (aux->next != NULL)
            {
                aux = aux->next;
            }
            while (aux->previous != NULL)
            {
                aux = aux->previous;
            }
        }
        i++;
    }
}

void print_hash_table(hash_table *hash, int key, int i, int j)
{
    node *aux = hash->table[i];

    if(key == i)
    {
        return;
    }

    while(!is_empty_list(aux))
    {
        if(j != 0)
        {
            printf(" -> %d", aux->item);
        }
        else{
            printf("%d -> %d", i, aux->item);
        }
        j = 1;
        aux = aux->next;
    }

    if((is_empty_list(aux)) && (j == 1))
    {
        printf(" -> \\\n");

    }
    else{
        printf("%d -> \\\n", i);
    }

    print_hash_table(hash, key, i+1, 0);
}
