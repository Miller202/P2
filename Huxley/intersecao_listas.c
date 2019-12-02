#include <stdio.h>
#include <stdlib.h>

void merge_sort(int *array, int *aux, int begin, int end);
void merge(int *array, int *aux, int begin1, int end1, int begin2, int end2);
void binary_search(int *array, int *quant, int size, int object);

int main()
{
    int i, quant=0;

    int *array1 = malloc(20 * sizeof(int));
    int *array2 = malloc(20 * sizeof(int));

    int *aux1 = malloc(20 * sizeof(int));
    int *aux2 = malloc(20 * sizeof(int));

    for (i = 0; i < 20; i++)
    {
        scanf("%d", &array1[i]);
    }

    merge_sort(array1, aux1, 0, 19);

    for (i = 0; i < 20; i++)
    {
        scanf("%d", &array2[i]);
    }

    merge_sort(array2, aux2, 0, 19);

    for (i = 0; i < 20; i++)
    {
        if (array2[i] != array2[i+1])
        {
            binary_search(array1, &quant, 20, array2[i]);
        }
    }

    if(quant == 0)
    {
        printf("VAZIO");
    }

    printf("\n");

    return 0;
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

void binary_search(int *array, int *quant, int size, int object)
{
    int i, begin=0;
    int end = size;

    while (begin <= end)
    {
        i = (begin + end)/2;

        if (array[i] < object)
        {
            begin = i+1;
        }
        else if (array[i] > object)
        {
            end = i-1;
        }
        else{
            printf("%d\n", array[i]);
            *quant += 1;
            return 0;
        }
    }

    if (begin > end)
    {
        return 0;
    }
}
