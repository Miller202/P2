#include <stdio.h>

void insertion_sort(int v[], int size)
{
    int i, j, key;

    for (i = 1; i < size; i++)
    {
        key = v[i];
        j = i - 1;

        while ((j >= 0) && (v[j] > key))
        {
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = key;
    }
}

int main()
{
	int i , n;
	scanf("%d", &n);
	int v[n];

	for (i = 0; i < n; i++)
    {
        scanf("%d", &v[i]);
	}

	insertion_sort(v, n);

	for (i = 0; i < n; i++)
    {
        printf("%d\n", v[i]);
	}

	return 0;
}
