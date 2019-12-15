#include <stdio.h>
#include <stdlib.h>

#define SIZE 11

typedef struct element element;
typedef struct hash_table hash_table;

struct element
{
    int key;
    int value;
};

struct hash_table
{
    element *table[SIZE];
};

hash_table* create_hash_table();
void put(hash_table *ht, int key, int value);
int get(hash_table *ht, int key);
void remove_hash(hash_table *ht, int key);
int contains_key(hash_table *ht, int key);
void print_hash_table(hash_table *ht);

int main()
{
    hash_table *ht = create_hash_table();
    put(ht, 5, 1000);
    put(ht, 2, 1500);
    put(ht, 9, 2000);
    remove_hash(ht, 2);
}

hash_table* create_hash_table()
{
    hash_table *new_hash_table = (hash_table*) malloc(sizeof(hash_table));

    int i;
    for (i = 0; i < SIZE; i++)
    {
        new_hash_table->table[i] = NULL;
    }

    return new_hash_table;
}

void put(hash_table *ht, int key, int value)
{
    int h = key % SIZE;
    while (ht->table[h] != NULL)
    {
        if (ht->table[h]->key == key)
        {
            ht->table[h]->value = value;
            break;
        }
        h = (h + 1) % SIZE;
    }
    if (ht->table[h] == NULL)
    {
        element *new_element = (element*) malloc(sizeof(element));
        new_element->key = key;
        new_element->value = value;
        ht->table[h] = new_element;
    }
}

int get(hash_table *ht, int key)
{
    int h = key % SIZE;
    while (ht->table[h] != NULL)
    {
        if (ht->table[h]->key == key)
        {
            return ht->table[h]->value;
        }
        h = (h + 1) % SIZE;
    }
    return -100;
}

void remove_hash(hash_table *ht, int key)
{
    int h = key % SIZE;
    while (ht->table[h] != NULL)
    {
        if (ht->table[h]->key == key)
        {
            ht->table[h]->key = -1;
        }
        h = (h + 1) % SIZE;
    }
}
