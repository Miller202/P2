#include <stdio.h>
#include <stdlib.h>

#define MAX 999

typedef struct heap heap;

struct heap
{
    int size;
    int items[MAX];
};

heap* create_heap();
void swap(int *item_1, int *item_2);
void max_heapify(heap *new_heap, int i);
void heap_sort(heap *new_heap);
void construct_heap_max(heap *new_heap);
void print_heap(heap *new_heap, int i, int aux);

int main()
{
    heap *new_heap = create_heap();

    int item, aux = 0, i = 1;
    while(scanf("%d", &item) != EOF)
    {
        new_heap->items[i] = item;

        if(aux == 0)
        {
            printf("Estado inicial: %d", item);
            aux = 1;
        }
        else{
            printf(" | %d", item);
        }

        i++;
    }
    printf("\n");

    new_heap->size = i;
    construct_heap_max(new_heap);
    new_heap->size = i - 1;

    printf("Estado Atual da Heap: ");
    print_heap(new_heap, 1, 0);

    heap_sort(new_heap);
    new_heap->size = i - 1;

    printf("Resultado Final: ");
    print_heap(new_heap, 1, 0);

    printf("\n");
}

heap *create_heap()
{
    heap *new_heap = (heap*) malloc(sizeof(heap));
    new_heap->size = 0;
    return new_heap;
}

void swap(int *item_1, int *item_2)
{
    int aux = 0;
    aux = *item_1;
    *item_1 = *item_2;
    *item_2 = aux;
}

void max_heapify(heap *new_heap, int i)
{
    int bigger;
    int left = 2 * i; // to get the left index
    int right = 2 * i + 1; // to get the right index

    if((new_heap->size >= left) && (new_heap->items[left] > new_heap->items[i]))
    {
        bigger = left;
    }
    else{
        bigger = i;
    }

    if((new_heap->size >= right) && (new_heap->items[right] > new_heap->items[bigger]))
    {
        bigger = right;
    }
    if(bigger != i)
    {
        swap(&new_heap->items[i], &new_heap->items[bigger]);
        max_heapify(new_heap, bigger);
    }
}

void heap_sort(heap *new_heap)
{
    int n = new_heap->size;
    int i = 0;
    for(i = n; i >= 2; i--)
    {
        printf("Maior elemento neste passo: %d\n", new_heap->items[1]);
        swap(&new_heap->items[1], &new_heap->items[i]);
        new_heap->size--;
        max_heapify(new_heap, 1);

        printf("Estado Atual da Heap: ");
        print_heap(new_heap, 1, 0);
    }
}

void construct_heap_max(heap *new_heap)
{
    int n = new_heap->size;
    int i = 0;
    for (i = n/2; i >= 1; i--)
    {
        max_heapify(new_heap, i);
    }
}

void print_heap(heap *new_heap, int i, int aux)
{
    if (i == new_heap->size + 1)
    {
        printf("\n");
        return;
    }
    if (aux == 0)
    {
        printf("%d", new_heap->items[i]);
        aux = 1;
    }
    else{
        printf(" | %d", new_heap->items[i]);
    }

    print_heap(new_heap, i+1, aux);
}
