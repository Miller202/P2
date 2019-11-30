#include <stdio.h>

void swap(int *a, int *b)
{
    int aux = *a;
    *a = *b;
    *b = aux;
}

void quick_sort(int v[], int size)
{
	if (size <= 1)
        return;

	else
    {
		int pivot = v[size / 2];
		int a = 0;
		int b = size - 1;

		while (a < b)
		{
			while (v[a] < pivot)
                a++;
			while (v[b] > pivot)
                b--;

			if (a < b)
			{
				swap(&v[a], &v[b]);
				a++;
			}

		}
		quick_sort(v, b);
		quick_sort(v + a, size - a);
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

	quick_sort(v, n);

	for (i = 0; i < n; i++)
    {
        printf("%d\n", v[i]);
    }

	return 0;
}
