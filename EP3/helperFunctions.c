#include "helperFunctions.h"
#include "ioFunctions.h"

int min(int a, int b)
{
	if (a < b)
	{
		return a;
	}
	return b;
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

void printTimeElapsed(struct timeval begin, struct timeval end)
{
	float elapsedTime = (float)(end.tv_sec - begin.tv_sec);
	elapsedTime += (float)(end.tv_usec - begin.tv_usec) / 1000000;
	printf("\nExecution Time (seconds): %9.5f\n\n", elapsedTime);
}