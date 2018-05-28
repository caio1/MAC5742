#include "functions.h"

int min(int64 a, int64 b){
	if (a < b){
		return a;
	}
	return b;
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
			M[i][j] = (double)rand()/1000;
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