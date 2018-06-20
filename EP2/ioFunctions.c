#include "ioFunctions.h"

int *readMatrices(int *matrixAmount, char *path)
{
	int * matrixList;

	FILE *file;
	file = fopen(path, "r");

	fscanf(file, "%d\n", matrixAmount);

	int listSize = *matrixAmount * MATRIX_WIDTH * MATRIX_WIDTH;
	int totalAmount = nextPowerOfTwo(*matrixAmount);
	int totalSize = totalAmount * MATRIX_WIDTH * MATRIX_WIDTH;

	matrixList = malloc(totalSize * sizeof(int));
	for (int i = listSize; i < totalSize; i++)
	{
		matrixList[i] = INT_MAX;
	}

	for (int l = 0; l < *matrixAmount; l += 1)
	{
		fscanf(file, "%*s\n");
		for (int i = 0; i < 9; i+=3)
		{
			if (fscanf(file, "%d %d %d\n",
					   &matrixList[l*9 + i], &matrixList[l*9 + i + 1], &matrixList[l*9 + i + 2]) == EOF)
			{
				printf("REACHED END OF FILE!!!\n\n\n");
			}
		}
	}
	return matrixList;
}

void saveMatrix(int **matrixList, int matrixAmount, char* path){
	FILE *fp;
	fp = fopen(path, "w");

	if(fp == NULL){
		printf("ERROR CREATING OUTPUT FILE\n");
	}

	fprintf(fp, "%d\n***\n", matrixAmount);

	for (int l = 0; l < matrixAmount; l++)
	{
		for (int i = 0; i < 9; i+=3)
		{
			fprintf(fp, "%d %d %d\n", matrixList[l*9 + i], matrixList[l*9 + i + 1], matrixList[l*9 + i + 2]);
		}
		fprintf(fp, "***\n");
	}
}
