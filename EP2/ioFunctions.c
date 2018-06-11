#include "ioFunctions.h"

int **readMatrices(int *matrixAmount, char *path)
{
	int ** matrixList;

	FILE *file;
	file = fopen(path, "r");

	fscanf(file, "%d\n", matrixAmount);

	matrixList = malloc(*matrixAmount * sizeof(int *));
	for (int i = 0; i < *matrixAmount; i++){
		matrixList[i] = malloc(9 * sizeof(int));
	}

	for (int l = 0; l < *matrixAmount; l++)
	{
		fscanf(file, "%*s\n");
		for (int i = 0; i < 9; i+=3)
		{
			if (fscanf(file, "%d %d %d\n",
					   &matrixList[l][i], &matrixList[l][i + 1], &matrixList[l][i + 2]) == EOF)
			{
				printf("REACHED END OF FILE!!!\n\n\n");
				// return matrixList;
			}
			// printf("%d %d %d\n",matrixList[l][i], matrixList[l][i+1], matrixList[l][i+2]);
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
			fprintf(fp, "%d %d %d\n", matrixList[l][i], matrixList[l][i + 1], matrixList[l][i + 2]);
		}
		fprintf(fp, "***\n");
	}
}
