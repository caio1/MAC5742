#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <pthread.h>
#include <limits.h>
#include <sys/types.h>
#include <mpi.h>

#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H
#define NUM_THREADS 4
#define ZERO pow(10, -32)

typedef struct thread_args
{
    double *partial_sum;
    double *partial_sum_sq;
    int64_t begin;
    int64_t end;
    int tid;

} thread_args, *thread_args_ptr;

int64_t M, N, k;
double *samples;
double f;
double fsquared;

int min(int a, int b);
int nextPowerOfTwo(int n);
double sum_array(double *a, int64_t n);
double randomSample(double min, double max);
void printTimeElapsed(struct timespec begin, struct timespec end);

#endif
