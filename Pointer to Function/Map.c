#include <stdio.h>
#include <stdlib.h>

void preencher_array(int *array, int n)
{
    int i;
    printf("Array -> ");
    for(i = 0; i < n; i++)
    {
        array[i] = i + 1;
        printf("%d ", array[i]);
    }
}

int square(int n)
{
    return n * n;
}

int factorial(int n)
{
    return n <= 1 ? 1 : n * factorial(n-1);
}

int *map(int (*f)(int), int *array, int n)
{
    int *newArray = malloc(sizeof(int) * n);

    int i;
    for (i = 0; i < n; i++)
    {
        newArray[i] = f(array[i]);
    }

    return newArray;
}

int main()
{
    int n;

    scanf("%d", &n);

    int array[n];

    preencher_array(array, n);

    int *SquareArray = map(square, array, n);
    int *FactorialArray = map(factorial, array, n);

    int i;
    printf("\nSquare Array -> ");
    for(i = 0; i < n; i++)
    {
        printf("%d ", SquareArray[i]);
    }
    printf("\nFactorial Array -> ");
    for(i = 0; i < n; i++)
    {
        printf("%d ", FactorialArray[i]);
    }

    free(SquareArray);
    free(FactorialArray);
}
