#include "functions.h"

int min(int64 a, int64 b){
	if (a < b){
		return a;
	}
	return b;
}

int max(int64 a, int64 b){
	if (a > b){
		return a;
	}
	return b;
}

int amountOfBlocks(int64 n){
	int t1 = max(2 * n - min(80, 2*n), 1);
	int t2 = sqrt(t1);
	int t3 = min(t2, 80);

	return t3;
}

void freeMatrix(double **M, int64 m)
{
	for (int64 i = 0; i < m; i++)
	{
		free(M[i]);
	}
	free(M);
}

//creating test matrixes
double **generateRandomMatrix(int64 height, int64 width){
	srand(time(NULL));

	double **M;

	M = malloc(height * sizeof(double*));

	for (int64 i = 0; i < height; i++)
	{
		M[i] = malloc(width * sizeof(double));
		for (int64 j = 0; j < width; j++)
		{
			M[i][j] = (double)rand()/10000;
		}
	}

	return M;
}

void printMatrix(double **M, int64 height, int64 width){
	for (int64 i = 0; i < height; i++)
	{
		printf("[");
		for (int64 j = 0; j < width; j++)
		{

			printf("%lf, ", M[i][j]);
		}
		printf("]\n");
	}
}


