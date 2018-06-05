#include "helperFunctions.h"
#include "ioFunctions.h"

double **multiplySequential(double **A, double **B, double **C, 
	int64 bm, int64 bn, int64 bp, int64 m, int64 n, int64 p)
{
	for (int64 i = bm; i < m; i++)
		for(int64 j = bn; j < n; j++)
			for (int64 k = bp; k < p; k++)
				C[i][j] += A[i][k]*B[k][j];

	return C;
}

double **multiplySequentialWithBColumnWise(double **A, double **B, double **C, 
	int64 bm, int64 bn, int64 bp, int64 m, int64 n, int64 p)
{
	for (int64 i = bm; i < m; i++)
		for(int64 j = bn; j < n; j++)
			for (int64 k = bp; k < p; k++)
				C[i][j] += A[i][k]*B[j][k];

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
		// multiplySequentialWithBColumnWise(A, B, C, from_m, from_n, k, to_m, to_n, min(k + block_size, matrix_size));

	pthread_exit(NULL);
}

double **multiplyBlocksPthreads(double **A, double **B, double **C, int64 m, int64 n, int64 p){

	printf("PTHREADS\n");
	// height of A (in blocks)
	int r = amountOfBlocks(m);
	int qr = m/r + (m % r != 0);
	// width of A/height of B (blocks)
	int s = amountOfBlocks(p);
	int qs = p / s + (p % s != 0);
	// width of B
	int t = amountOfBlocks(n);
	int qt = n / t + (n % t != 0);

	int nthreads = r*t;
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

			thread_index ++;
		}
	}

	for (int i = 0; i < nthreads; i++)
	{
		pthread_join(threads[i], NULL);
	}

	return C;
}

double **multiplyBlocksOpenMP(double **A, double **B, double **C, int64 m, int64 n, int64 p)
{
	printf("OPENMP\n");
	// height of A (in blocks)
	int r = amountOfBlocks(m);
	int qr = m / r + (m % r != 0);
	// width of A/height of B (blocks)
	int s = amountOfBlocks(p);
	int qs = p / s + (p % s != 0);
	// width of B
	int t = amountOfBlocks(n);
	int qt = n / t + (n % t != 0);


	omp_set_num_threads(4);

	for (int64 i = 0; i < m; i += qr)
	{
		for (int64 j = 0; j < n; j += qt)
		{
			int64 k = 0;
			#pragma omp parallel for private(k)
			for (k = 0; k < p; k+=qs){
				// printf("My number is :%d\n", omp_get_thread_num());
				multiplySequential(A, B, C, i, j, k, min(i + qr, m), min(j + qt, n), min(k + qs, p));
				// multiplySequentialWithBColumnWise(A, B, C, i, j, k, min(i + qr, m), min(j + qt, n), min(k + qs, p));
			}
		}
	}

	return C;
}


int main(int argc, char* argv[]) {

	struct timeval start, stop;
	
	if (argc != 5)
	{
		printf("Usage: %s <implementacao> <caminho_matriz_A> <caminho_matriz_B> <caminho_matriz_C>\n", argv[0]);
		return 3;
	}

	double **A, **B, **C;
	int64 m, n, p;

	A = readMatrix(&m, &p, argv[2]);
	B = readMatrix(&p, &n, argv[3]);
	// B = readMatrixColumnWise(&p, &n, argv[3]);


	C = malloc(m * sizeof(double *));
	for (int64 i = 0; i < m; i++)
	{
		C[i] = calloc(n, sizeof(double));
	}

	gettimeofday(&start, NULL);

	if(strcmp(argv[1], "p") == 0){
		multiplyBlocksPthreads(A, B, C, m, n, p);
	}
	else if (strcmp(argv[1], "o") == 0){
		multiplyBlocksOpenMP(A, B, C, m, n, p);
	}
	else{
		multiplySequential(A, B, C, 0, 0, 0, m, n, p);	
	}

	gettimeofday(&stop, NULL);

	double time_elapsed = (1000.0 * (stop.tv_sec - start.tv_sec) + (0.001 * (stop.tv_usec - start.tv_usec)));
	printf("Time elapsed: %fs\n", time_elapsed);

	saveMatrix(C, m, n, argv[4]);

	// double **M;
	// M = generateRandomMatrix(1000, 1000);
	// saveMatrix(M, 1000, 1000, "1000x1000");
	// free(M);

	freeMatrix(A, m);
	freeMatrix(B, p);
	freeMatrix(C, m);

	return 0;
}
