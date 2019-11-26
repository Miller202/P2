#include <stdio.h>
#include <stdlib.h>

int binary_search(int *v, int size, int element)
{
    int begin, end, middle;
    begin = 0;
    end = size - 1;

    while (begin <= end)
    {
        middle = (begin + end) / 2;

        if (v[middle] < element)
        {
            begin = middle + 1;
        }
        else if (v[middle] > element)
        {
            end = middle - 1;
        }
        else{
            return middle;
        }
    }
    return -1;
}

int main()
{
    int i;
    int v[10];

    for(i = 0; i < 10; i++)
    {
        scanf("%d", &v[i]);
    }

    int value = binary_search(v, 10, 5);

    printf("%d\n", value);
}
