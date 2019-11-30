#include <stdio.h>

void swap(int *a , int *b)
{
    int aux = *a;
    *a = *b;
    *b = aux;
}

void selection_sort(int v[], int n)
{
    int i, j, min;

    for (i = 0; i < n; i++)
    {
        min = i;

        for (j = i+1; j < n; j++)
        {
            if (v[j] < v[min])
            {
                min = j;
            }
        }
        swap(&v[i], &v[min]);
    }
}

int main()
{
	int i, n;
	scanf("%d", &n);
	int v[n];

	for (i = 0; i < n; i++)
    {
        scanf("%d", &v[i]);
    }

	selection_sort(v, n);

	for (i = 0; i < n; i++)
    {
        printf("%d\n", v[i]);
    }

	return 0;
}
