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