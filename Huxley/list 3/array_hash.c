#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hash_calc(char *string, int size, int aux);

int main()
{
    int i, j, value;
    char string[99];
    int aux = 0;

    int n;
    scanf("%d", &n);

    for(i = 0; i < n; i++)
    {
        int l;
        scanf("%d", &l);

        for(j = 0; j < l; j++)
        {
            scanf("%s", string);
            int size = strlen(string);
            value += hash_calc(string, size, aux);
            aux++;
        }
        printf("%d\n", value);
        aux = 0;
        value = 0;
    }
    return 0;
}

int hash_calc(char *string, int size, int aux)
{
    int quant = 0, i = 0;

    while(i != size)
    {
        quant += (string[i] - 'A') + aux + i;
        i++;
    }
    return quant;
}
