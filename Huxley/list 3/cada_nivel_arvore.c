#include <stdio.h>

#define no 2

void imprimirValores(int n, int menor[], int maior[])
{
    int i;

    for (i = 0; i < n; i++)
    {
        if (menor[i] != 404)
        {
    	    printf("Nivel %d: Maior = %d, Menor = %d\n", i+1, maior[i], menor[i]);
        }
    }
}

void encontrarValores(int i, int nivel, int n, int array[n], int matriz[n][no], int menor[n], int maior[n])
{
	if (i != -1)
	{
	    if (array[i] < menor[nivel])
		{
			menor[nivel] = array[i];
		}
		if (array[i] > maior[nivel])
		{
			maior[nivel] = array[i];
		}

		encontrarValores(matriz[i][0], nivel+1, n, array, matriz, menor, maior);
		encontrarValores(matriz[i][1], nivel+1, n, array, matriz, menor, maior);
	}
}

void preencher(int n, int menor[], int maior[])
{
    int i;

    for (i = 0; i < n; i++)
	{
		menor[i] = 404;
		maior[i] = -404;
	}
}

void lerEntrada(int n, int array[], int matriz[][no])
{
    int i, j;

    for (i = 0; i < n; i++)
	{
	    scanf("%d", &array[i]);

		for (j = 0; j < no; j++)
		{
			scanf("%d", &matriz[i][j]);
		}
	}
}

int main()
{
	int n;

	scanf("%d", &n);

	int array[n], matriz[n][no];
	int menor[n], maior[n];

    lerEntrada(n, array, matriz);

	preencher(n, menor, maior);

    encontrarValores(0, 0, n, array, matriz, menor, maior);

    imprimirValores(n, menor, maior);

	return 0;
}
