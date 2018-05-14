#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include "functions.h"

double ** readMatrix(unsigned long long* height, unsigned long long* width, char* path){
	FILE *fp;
	fp = fopen(path, "r");
	double ** matrix;

	fscanf(fp, "%llu %llu", height, width);

	matrix = malloc(*height * sizeof(double*));
	for (unsigned long long i = 0; i < *height; i++){
		matrix[i] = malloc(*height * sizeof(double));
		memset(matrix[i], 0, *width * sizeof(double));
	}

	unsigned long long x, y;
	double value;

	while (fscanf(fp, "%llu %llu %lf", &y, &x, &value) != EOF){
		matrix[y-1][x-1] = value;
	}

	return matrix;
}

double **multiplySequential(double **A, double **B, unsigned long long m, unsigned long long n)
{
	double **C;

	C = malloc(m * sizeof(double *));

	for (unsigned long long i = 0; i < m; i++)
	{
		C[i] = malloc(m * sizeof(double));
		for(unsigned long long j = 0; j < n; j++){
			C[i][j] = 0.0;
		}
	}

	return C;
}


int main(int argc, char* argv[]) {

	if (argc != 4)
	{
		printf("Usage: %s <caminho_matriz_A> <caminho_matriz_B> <caminho_matriz_C>\n", argv[0]);
		return 3;
	}

	double **A, **B, **C;
	unsigned long long m, n, p;

	A = readMatrix(&m, &p, "testMatrix1");
	B = readMatrix(&p, &n, "testMatrix2");
	C = multiplySequential(A, B, m, n);


	printf("height = %llu\n", p);
	printf("width = %llu\n", n);

	for (unsigned long long i = 0; i < p; i++)
	{
		printf("[");
		for (unsigned long long j = 0; j < n; j++)
		{
			printf(" %lf,", B[i][j]);
		}
		printf("]\n");
	}

	return(0);
}
