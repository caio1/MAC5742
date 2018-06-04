#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <pthread.h>
#include <omp.h>

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef unsigned long long int64;


typedef struct thread_args{
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


int min(int64 a, int64 b);
int max(int64 a, int64 b);
int amountOfBlocks(int64 n);
double **generateRandomMatrix(int64 height, int64 width);
void printMatrix(double **M, int64 height, int64 width);
void freeMatrix(double **M, int64 m);

#endif
