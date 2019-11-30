#include <stdio.h>

void swap(int *a , int *b)
{
    int aux = *a;
    *a = *b;
    *b = aux;
}

void bubble_sort(int v[], int size)
{
    int j , i;

    for (j = 1; j <= size; j++)
    {
        for (i = 0; i < size - 1; i++)
        {
            if (v[i] > v[i+1])
            {
                swap(&v[i], &v[i+1]);
            }
        }
    }
}

int main()
{
	int n , i;
	scanf("%d", &n);
	int v[n];

	for (i = 0; i < n; i++)
    {
        scanf("%d", &v[i]);
    }

    bubble_sort(v, n);

	for (i = 0; i < n; i++)
    {
        printf("%d\n", v[i]);
    }

	return 0;
}
