#include "helperFunctions.h"
#include "ioFunctions.h"
#include "reduction.h"

void drawSamples()
{
	int64_t i;
	for (i = 0; i < N; i++)
	{
		samples[i] = randomSample(ZERO, 1);
	}
}

double fun(double x)
{
	double result = (sin((2 * M + 1) * M_PI * x) * cos(2 * M_PI * k * x)) / sin(M_PI * x);
	return result;
}

void calculate_f_sequential()
{
	double sum = 0;
	double sumsq = 0;

	f = 0;
	fsquared = 0;

	int64_t i;
	for (i = 0; i < N; i++)
	{
		double f_i = fun(samples[i]);
		double fsq_i = pow(f_i, 2);
		sum += f_i;
		sumsq += fsq_i;
	}
	f = sum / N;
	fsquared = sumsq / N;
}

void *calculate_f_pthreads(void *args)
{
	thread_args_ptr threadArgs = (thread_args_ptr)args;

	double *partial_sum = threadArgs->partial_sum;
	double *partial_sum_sq = threadArgs->partial_sum_sq;
	int64_t begin = threadArgs->begin;
	int64_t end = threadArgs->end;
	int tid = threadArgs->tid;

	int64_t i;
	// printf("%d: begin = %lld\nend = %lld\n\n", tid, begin, end);

	for (i = begin; i < end; i++)
	{
		double f_i = fun(samples[i]);
		double fsq_i = pow(f_i, 2);

		partial_sum[tid] += f_i;
		partial_sum_sq[tid] += fsq_i;
	}

	pthread_exit(NULL);
}

void calculate_f_CPU()
{
	double *partial_sum = calloc(NUM_THREADS, sizeof(double));
	double *partial_sum_sq = calloc(NUM_THREADS, sizeof(double));

	pthread_t threads[NUM_THREADS];
	thread_args threadsArgs[NUM_THREADS];
	int tid;
	for (tid = 0; tid < NUM_THREADS; tid++)
	{
		threadsArgs[tid].tid = tid;
		threadsArgs[tid].partial_sum = partial_sum;
		threadsArgs[tid].partial_sum_sq = partial_sum_sq;
		threadsArgs[tid].begin = (int64_t)ceil(tid * (N * 1.0 / NUM_THREADS));
		threadsArgs[tid].end = (int64_t)ceil((tid + 1) * (N * 1.0 / NUM_THREADS));

		pthread_create(&(threads[tid]), NULL, calculate_f_pthreads, &(threadsArgs[tid]));
	}

	for (tid = 0; tid < NUM_THREADS; tid++)
	{
		pthread_join(threads[tid], NULL);
	}

	f = 0;
	fsquared = 0;
	int i;
	for (i = 0; i < NUM_THREADS; i++)
	{
		f += partial_sum[i];
		fsquared += partial_sum_sq[i];
	}

	f = f / N;
	fsquared = fsquared / N;

	printf("f = %lf\n", f);
	printf("f_squared = %lf\n", fsquared);
}

double calculateIntegral(double a, double b, double sig)
{
	return (b - a) * (f + sig * sqrt((fsquared - pow(f, 2)) / N));
}

int main(int argc, char *argv[])
{
	struct timespec begin, end;
	srand(time(NULL));

	MPI_Init(NULL, NULL);

	if (argc < 4)
	{
		printf("Usage: %s <numero_de_amostras> <parametro_k> <parametro_M>\n", argv[0]);
		return 3;
	}

	N = strtoll(argv[1], NULL, 10);
	k = strtoll(argv[2], NULL, 10);
	M = strtoll(argv[3], NULL, 10);
	samples = malloc(N * sizeof(double));

	drawSamples();

	clock_gettime(CLOCK_REALTIME, &begin);
	printf("\nExecutando com pthreads\n");
	calculate_f_CPU();
	double integral_plus = 2 * calculateIntegral(ZERO, 0.5, 1);
	double integral_minus = 2 * calculateIntegral(ZERO, 0.5, -1);
	printf("Integrais: \nSoma: %lf\nSubracao: %lf\n", integral_plus, integral_minus);
	clock_gettime(CLOCK_REALTIME, &end);

	printTimeElapsed(begin, end);

	clock_gettime(CLOCK_REALTIME, &begin);
	printf("\nExecutando sequencialmente\n");

	calculate_f_sequential();
	integral_plus = 2 * calculateIntegral(ZERO, 0.5, 1);
	integral_minus = 2 * calculateIntegral(ZERO, 0.5, -1);
	printf("Integrais: \nSoma: %lf\nSubracao: %lf\n", integral_plus, integral_minus);
	clock_gettime(CLOCK_REALTIME, &end);
	printTimeElapsed(begin, end);

	clock_gettime(CLOCK_REALTIME, &begin);

	reduceOnGPU();
	clock_gettime(CLOCK_REALTIME, &end);
	printTimeElapsed(begin, end);

	free(samples);

	return 0;
}
