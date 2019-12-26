#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct hash hash;
typedef struct node node;

struct node
{
    int item;
    node *next, *prev;
};

struct hash
{
    int quant;
    node **table;
};

hash* create_hash(int size);
node* node_add(int item);
node* begin_add(node *head, int item);
int ADD(hash *new_hash, int item, int size, int *cont);
int DEL(hash *new_hash, int item, int size, int *cont);
int HAS(hash *new_hash, int item, int size, int *cont);
int PRT_LIST(hash *new_hash, int size);
void REHASH_ADD(hash *new_hash, int item, int size);
hash* REHASH(hash *new_hash, int size);

int main()
{
    char string[5];
    int size = 7, item = 0, value = 0, cont = 0, aux = 0;
    hash *new_hash = create_hash(size);

    while (scanf("%s", string) != EOF)
    {
        printf("%d ", value);
        if (strcmp(string, "ADD") == 0)
        {
            scanf("%d", &item);
            aux = ADD(new_hash, item, size, &cont);
            printf("%d %d\n", aux, cont);
            cont = 0;
            if (aux == 1)
            {
                new_hash->quant++;
            }
        }
        else if (strcmp(string, "DEL") == 0)
        {
            scanf("%d", &item);
            aux = DEL(new_hash, item, size, &cont);
            printf("%d %d\n", aux, cont);
            cont = 0;
            if (aux == 1)
            {
                new_hash->quant--;
            }
        }
        else if (strcmp(string, "HAS") == 0)
        {
            scanf("%d", &item);
            aux = HAS(new_hash, item, size, &cont);
            printf("%d %d\n", aux, cont);
            cont = 0;
        }
        else if (strcmp(string, "PRT") == 0)
        {
            printf("%d %d %d\n", size, new_hash->quant, PRT_LIST(new_hash, size));
        }

        if (((float)(new_hash->quant)/(float)(size)) >= 0.75)
        {
            size = (2 * size) - 1;
            new_hash = REHASH(new_hash, size);
        }
        value++;
    }
}

hash* create_hash(int size)
{
    hash *new_hash_table = (hash*) malloc(sizeof(hash));
    new_hash_table->table = (node*) malloc(size * sizeof(node));

    int i;
    for (i = 0; i < size; i++)
    {
        new_hash_table->table[i] = NULL;
    }

    return new_hash_table;
}

node* node_add(int item)
{
    node* new_node = (node*) malloc(sizeof(node));
    new_node->item = item;
    new_node->next = new_node->prev = NULL;
    return new_node;
}

node* begin_add(node *head, int item)
{
    node *new_node = node_add(item);
	if(head != NULL)
    {
		new_node->next = head;
		head->prev = new_node;
	}
	return new_node;
}

int ADD(hash *new_hash, int item, int size, int *cont)
{
    if(new_hash == NULL)
    {
        return 0;
    }
    int key = item % size;

    if(new_hash->table[key] != NULL)
    {
        node *head = new_hash->table[key];
        node *aux = head;

        if(aux->next != NULL)
        {
            while(aux != NULL)
            {
                *cont += 1;
                if(aux->item == item)
                {
                    return 0;
                    break;
                }
                if(aux->next == NULL)
                {
                    break;
                }
                aux = aux->next;
            }
            if(aux->item != item)
            {
                head = begin_add(head, item);
                new_hash->table[key] = head;
                return 1;
            }
        }
        else{
            *cont = 1;
            if(aux->item == item)
            {
                return 0;
            }
            else{
                head = begin_add(head, item);
                new_hash->table[key] = head;
                return 1;
            }
        }
    }
    else{
        node *head = NULL;
        head = begin_add(head, item);
        new_hash->table[key] = head;
        return 1;
    }
}

int DEL(hash *new_hash, int item, int size, int *cont)
{
    if(new_hash == NULL)
    {
        return 0;
    }
    int key = item % size;
    node *aux = new_hash->table[key];

    while(aux != NULL)
    {
        *cont += 1;
        if(aux->item == item)
        {
            if(aux->next == NULL && aux->prev == NULL)
            {
                new_hash->table[key] = NULL;
                free(aux);
            }
            else if(aux->next == NULL)
            {
                node *previous = aux->prev;
                previous->next = NULL;
                aux->prev = NULL;
                free(aux);
            }
            else if(aux->prev == NULL)
            {
                node *temp = aux->next;
                new_hash->table[key] = temp;
                temp->prev = NULL;
                free(aux);
            }
            else{
                node *temp = aux->next;
                node *previous = aux->prev;
                previous->next = temp;
                temp->prev = previous;
                free(aux);
            }
            return 1;
        }
        aux = aux->next;
    }
    return 0;
}

int HAS(hash *new_hash, int item, int size, int *cont)
{
    int key = item % size;
    node *aux = new_hash->table[key];

    while(aux != NULL)
    {
        *cont += 1;
        if(aux->item == item)
        {
            return 1;
        }
        aux = aux->next;
    }
    return 0;
}

int PRT_LIST(hash *new_hash, int size)
{
    int aux = 0, cont = 0, prt = 0;

    while(size != aux)
    {
        node *tb = new_hash->table[aux];

        while(tb != NULL)
        {
            cont++;
            tb = tb->next;
        }
        if(prt < cont)
        {
            prt = cont;
        }
        aux++;
        cont = 0;
    }
    return prt;
}

void REHASH_ADD(hash *new_hash, int item, int size)
{
    if(new_hash == NULL)
    {
        return 0;
    }
    new_hash->quant++;
    int key = item % size;

    if(new_hash->table[key] != NULL)
    {
        node *aux = new_hash->table[key];
        aux = begin_add(aux, item);
        new_hash->table[key] = aux;
    }
    else{
        node *head = NULL;
        head = begin_add(head, item);
        new_hash->table[key] = head;
    }
}

hash* REHASH(hash *new_hash, int size)
{
    hash *long_hash = create_hash(size);

    int aux = 0;
    while(size != aux)
    {
        node *tb = new_hash->table[aux];
        while(tb != NULL)
        {
            REHASH_ADD(long_hash, tb->item, size);
            tb = tb->next;
        }
        aux++;
    }
    return long_hash;
}
