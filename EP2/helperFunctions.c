#include "helperFunctions.h"
#include "ioFunctions.h"

int min(int a, int b){
	if (a < b){
		return a;
	}
	return b;
}

int nextPowerOfTwo(int n){
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

void generateRandomInputFile(int matrixAmount){
	int *matrixList[matrixAmount];
	for (int l = 0; l < matrixAmount; l++)
	{
		matrixList[matrixAmount] = generateRandomMatrix(3, 3);
	}
	saveMatrix(matrixList, matrixAmount, "in2");
	
}

//creating test matrixes
int *generateRandomMatrix(int height, int width){
	srand(time(NULL));

	int *M;

	M = malloc(height * width * sizeof(int*));

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			M[3 * i + j] = rand() % (INT_MAX/2 - INT_MIN/2) + INT_MIN/2;
		}
	}

	return M;
}

void printMatrix(int *M, int height, int width){
	for (int i = 0; i < height; i++)
	{
		printf("[");
		for (int j = 0; j < width; j++)
		{
			printf("%d, ", M[3*i + j]);
		}
		printf("]\n");
	}
}


