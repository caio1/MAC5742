#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <pthread.h>

#include "functions.h"

typedef unsigned long long int64;

typedef struct thread_args
{
	double ** A;
	double ** B;
	double ** C;
	int64 from_m;
	int64 from_n;
	int64 to_m;
	int64 to_n;
	int64 block_size;
	int64 matrix_size;

} thread_args, *thread_args_ptr;


int min(int64 a, int64 b)
{
	if (a < b)
	{
		return a;
	}
	return b;
}

double ** readMatrix(unsigned long long* height, unsigned long long* width, char* path){
	FILE *fp;
	fp = fopen(path, "r");
	double ** matrix;

	fscanf(fp, "%llu %llu", height, width);

	matrix = malloc(*height * sizeof(double*));
	for (unsigned long long i = 0; i < *height; i++){
		matrix[i] = calloc(*width, sizeof(double));
	}

	unsigned long long x, y;
	double value;

	while (fscanf(fp, "%llu %llu %lf", &y, &x, &value) != EOF){
		matrix[y-1][x-1] = value;
	}

	return matrix;
}

void saveMatrix(double **M, int64 height, int64 width, char* path){
	FILE *fp;
	fp = fopen(path, "w");

	fprintf(fp, "%llu %llu\n", height, width);

	for (int64 i = 0; i < height; i++)
	{
		for (int64 j = 0; j < width; j++)
		{
			fprintf(fp, "%llu %llu %lf\n", i + 1, j + 1, M[i][j]);
		}
	}
}

void sumMatrices(double **A, double **B, double **C, int64 m, int64 n)
{
	for (int64 i = 0; i < m; i++)
		for(int64 j = 0; j < n; j++)
			C[i][j] = A[i][j] + B[i][j];
}

double **multiplySequential(double **A, double **B, double **C, 
	int64 bm, int64 bn, int64 bp, int64 m, int64 n, int64 p)
{
	printf("A from [%llu, %llu] to [%llu, %llu]\n", bm, bp, m, p);
	printf("B from [%llu, %llu] to [%llu, %llu]\n\n", bp, bn, p, n);
	for (int64 i = bm; i < m; i++)
		for(int64 j = bn; j < n; j++)
			for (int64 k = bp; k < p; k++)
				C[i][j] += A[i][k]*B[k][j];

	return C;
}

void *multTest1(thread_args_ptr args){

	double **A = args->A;
	double **B = args->B;
	double **C = args->C;
	int64 from_m = args->from_m;
	int64 from_n = args->from_n;
	int64 to_m = args->to_m;
	int64 to_n = args->to_n;
	int64 block_size = args->block_size;
	int64 matrix_size = args->matrix_size;

	for (int64 k = 0; k < matrix_size; k+=block_size)
		multiplySequential(A, B, C, from_m, from_n, k, to_m, to_n, min(k + block_size, matrix_size));
}

double **multiplyBlocks(double **A, double **B, double **C, int64 m, int64 n, int64 p){


	// height of A (in blocks)
	int r = 4;
	int qr = m/r + (m % r != 0);
	// width of A/height of B (blocks)
	int s = 4;
	int qs = p / s + (p % s != 0);
	// width of B
	int t = 4;
	int qt = n / t + (n % t != 0);

	pthread_t threads[r*s];
	thread_args threadsArgs[r*s];

	for (int64 i = 0; i < m; i+=qr){
		for (int64 j = 0; j < n; j+=qt){
			int thread_index = 0;

			threadsArgs[thread_index].A = A;
			threadsArgs[thread_index].B = B;
			threadsArgs[thread_index].C = C;
			threadsArgs[thread_index].from_m = i;
			threadsArgs[thread_index].from_n = j;
			threadsArgs[thread_index].to_m = min(i + qr, m);
			threadsArgs[thread_index].to_n = min(j + qt, n);
			threadsArgs[thread_index].block_size = qs;
			threadsArgs[thread_index].matrix_size = p;


			pthread_create(&(threads[thread_index]), NULL, multTest1, &(threadsArgs[thread_index]));
			// for (int64 k = 0; k < p; k+=qs)
			// 	multiplySequential(A, B, C, i, j, k,
			// 					   min(i + qr, m), min(j + qt, n), min(k + qs, p));

			thread_index ++;
		}
	}

	return C;
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

int main(int argc, char* argv[]) {

	if (argc != 4)
	{
		printf("Usage: %s <caminho_matriz_A> <caminho_matriz_B> <caminho_matriz_C>\n", argv[0]);
		return 3;
	}

	double **A, **B, **C;
	unsigned long long m, n, p;

	A = readMatrix(&m, &p, "4x4A");
	B = readMatrix(&p, &n, "4x4B");

	// A = readMatrix(&m, &p, argv[1]);
	// B = readMatrix(&p, &n, argv[2]);

	C = malloc(m * sizeof(double *));
	for (unsigned long long i = 0; i < m; i++)
	{
		C[i] = calloc(n, sizeof(double));
	}

	multiplyBlocks(A, B, C, m, n, p);
	// multiplySequential(A, B, C, 0, 0, 0, m, n, p);
	saveMatrix(C, m, n, "4x4C");

	// double **M;
	// M = generateRandomMatrix(6, 10);
	// saveMatrix(M, 6, 10, "6x10");

	return(0);
}
