#include <stdio.h>

int linear_search(int *v, int size, int element)
{
    int i;
    for (i = 0; i < size; i++)
    {
        if (v[i] == element)
        {
            return i;
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

    int value = linear_search(v, 10, 5);

    printf("%d\n", value);
}

