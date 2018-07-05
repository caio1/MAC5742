#include "helperFunctions.h"
#include "CPUImplementations.h"

int min(int a, int b)
{
	if (a < b)
	{
		return a;
	}
	return b;
}

double fun(double x)
{
	return (sin((2 * M + 1) * M_PI * x) * cos(2 * M_PI * k * x)) / sin(M_PI * x);
}

int nextPowerOfTwo(int n)
{
	return pow(2, ceil(log(n) / log(2)));
}

double sum_array(double *a, int64_t n)
{
	double sum = 0;
	int64_t i;
	for (i = 0; i < n; i++)
	{
		sum += a[i];
	}
	return sum;
}

double randomSample(double min, double max)
{
	double range = (max - min);
	double div = RAND_MAX / range;
	return min + (rand() / div);
}

void printTimeElapsed(struct timespec begin, struct timespec end)
{
	float elapsedTime = (float)(end.tv_sec - begin.tv_sec);
	elapsedTime += (float)(end.tv_nsec - begin.tv_nsec) / 1000000000;
	printf("\nExecution Time (seconds): %9.5f\n\n", elapsedTime);
}