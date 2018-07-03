#include "helperFunctions.h"
#include "ioFunctions.h"

int min(int a, int b)
{
	if (a < b)
	{
		return a;
	}
	return b;
}

int nextPowerOfTwo(int n)
{
	return pow(2, ceil(log(n) / log(2)));
}

void freeMatrixList(int **matrixList, int matrixAmount)
{
	for (int i = 0; i < matrixAmount; i++)
	{
		free(matrixList[i]);
	}
	free(matrixList);
}

int compareResults(int *sequential, int *gpu)
{
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		if (sequential[i] != gpu[i])
		{
			return 0;
		}
	}
	return 1;
}

void generateRandomInputFile(int matrixAmount, char *path)
{
	srand(time(NULL));
	printf("generating input file\n");
	int *matrixList[matrixAmount];
	for (int l = 0; l < matrixAmount; l++)
	{

		matrixList[l] = generateRandomMatrix(3, 3);
	}
	printf("finished generating random matrices\n");

	saveMatrix(matrixList, matrixAmount, path);
}

//creating test matrixes
int *generateRandomMatrix(int height, int width)
{
	int *M;

	M = malloc(height * width * sizeof(int));

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			M[3 * i + j] = rand() % (10000) - 10000;
		}
	}

	return M;
}

void printMatrix(int *M, int height, int width)
{
	for (int i = 0; i < height; i++)
	{
		printf("[");
		for (int j = 0; j < width; j++)
		{
			printf("%d, ", M[3 * i + j]);
		}
		printf("]\n");
	}
}
