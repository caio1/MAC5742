#include "functions.h"
#include "iofunctions.h"

double **multiplySequential(double **A, double **B, double **C, 
	int64 bm, int64 bn, int64 bp, int64 m, int64 n, int64 p)
{
	// printf("A from [%llu, %llu] to [%llu, %llu]\n", bm, bp, m, p);
	// printf("B from [%llu, %llu] to [%llu, %llu]\n\n", bp, bn, p, n);
	for (int64 i = bm; i < m; i++)
		for(int64 j = bn; j < n; j++)
			for (int64 k = bp; k < p; k++)
				C[i][j] += A[i][k]*B[k][j];

	return C;
}

void *multBlocksPthreads(void* args){

	thread_args_ptr threadArgs = (thread_args_ptr) args;

	double **A = threadArgs->A;
	double **B = threadArgs->B;
	double **C = threadArgs->C;
	int64 from_m = threadArgs->from_m;
	int64 from_n = threadArgs->from_n;
	int64 to_m = threadArgs->to_m;
	int64 to_n = threadArgs->to_n;
	int64 block_size = threadArgs->block_size;
	int64 matrix_size = threadArgs->matrix_size;

	for (int64 k = 0; k < matrix_size; k+=block_size)
		multiplySequential(A, B, C, from_m, from_n, k, to_m, to_n, min(k + block_size, matrix_size));

	pthread_exit(NULL);
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

	int nthreads = r*s;
	pthread_t threads[nthreads];
	thread_args threadsArgs[nthreads];

	int thread_index = 0;
	for (int64 i = 0; i < m; i+=qr){
		for (int64 j = 0; j < n; j+=qt){

			threadsArgs[thread_index].A = A;
			threadsArgs[thread_index].B = B;
			threadsArgs[thread_index].C = C;
			threadsArgs[thread_index].from_m = i;
			threadsArgs[thread_index].from_n = j;
			threadsArgs[thread_index].to_m = min(i + qr, m);
			threadsArgs[thread_index].to_n = min(j + qt, n);
			threadsArgs[thread_index].block_size = qs;
			threadsArgs[thread_index].matrix_size = p;


			pthread_create(&(threads[thread_index]), NULL, multBlocksPthreads, &(threadsArgs[thread_index]));
			// for (int64 k = 0; k < p; k+=qs)
			// 	multiplySequential(A, B, C, i, j, k,
			// 					   min(i + qr, m), min(j + qt, n), min(k + qs, p));

			thread_index ++;
		}
	}

	for (int i = 0; i < nthreads; i++)
	{
		pthread_join(threads[i], NULL);
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
	int64 m, n, p;

	A = readMatrix(&m, &p, "8x6");
	B = readMatrix(&p, &n, "6x10");

	// A = readMatrix(&m, &p, argv[1]);
	// B = readMatrix(&p, &n, argv[2]);

	C = malloc(m * sizeof(double *));
	for (int64 i = 0; i < m; i++)
	{
		C[i] = calloc(n, sizeof(double));
	}

	multiplySequential(A, B, C, 0, 0, 0, m, n, p);
	saveMatrix(C, m, n, "sequential");
	// multiplyBlocks(A, B, C, m, n, p);
	// saveMatrix(C, m, n, "blocks");

	// double **M;
	// M = generateRandomMatrix(6, 10);
	// saveMatrix(M, 6, 10, "6x10");

	return(0);
}
