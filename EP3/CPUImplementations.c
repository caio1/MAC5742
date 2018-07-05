#include "CPUImplementations.h"

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

	free(partial_sum);
	free(partial_sum_sq);

	f = f / N;
	fsquared = fsquared / N;

	// printf("f = %lf\n", f);
	// printf("f_squared = %lf\n", fsquared);
}