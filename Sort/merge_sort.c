#include <stdio.h>
#include <limits.h>

void merge (int a[], int p, int q, int r)
{
    int n1 = q - p + 1;
    int n2 = r - q ;

    int i, j, k, L[n1 + 1], R[n2 + 1];

    for (int i = 1; i <= n1; i++)
    {
        L[i] = a[p + i - 1];
    }

    for (int j = 1; j <= n1; j++)
    {
         R[j] = a[q + j];
    }

    L[n1 + 1] = INT_MAX;
    R[n2 + 1] = INT_MAX;

    i = 1 , j = 1;

    for (k = p; k <= r; k++)
    {
        if (L[i] <= R[j])
        {
            a[k] = L[i];
            i++ ;
        }
        else{
            a[k] = R[j];
            j++;
        }
    }
}

void merge_sort(int a[], int p, int r)
{
    int q;

    if (p < r)
    {
        q = (p + r)/2;
        merge_sort(a, p, q);
        merge_sort(a, q+1, r);
        merge(a, p, q, r);
    }
}

int main()
{
	int i, n;
	scanf("%d", &n);
	int a[n];

	for (i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
	}

	merge_sort(a , 0, n-1);

	for (i = 0; i < n; i++)
    {
        printf("%d\n", a[i]);
	}

	return 0;
}
