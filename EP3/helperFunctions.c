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

double randomSample(double min, double max)
{
	double range = (max - min);
	double div = RAND_MAX / range;
	return min + (rand() / div);
}

void printTimeElapsed(struct timeval begin, struct timeval end)
{
	float elapsedTime = 1000000 * (float)(end.tv_sec - begin.tv_sec);
	elapsedTime += (float)(end.tv_usec - begin.tv_usec);
	printf("\nExecution Time (microseconds): %9.2f\n\n", elapsedTime);
}