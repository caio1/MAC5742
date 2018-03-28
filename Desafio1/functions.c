#include <functions.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


double compareValues(int* A, int n) {


	double start, stop, elapsed;
    start = (double) clock () / CLOCKS_PER_SEC;

	for(unsigned int i=0; i < n; ++i)
	{
		if(A[i] < 5000){
			A[i]++;
		}
	}

	stop = (double) clock () / CLOCKS_PER_SEC;
    elapsed = stop - start;

	return elapsed;
}

int comp(const void * a, const void * b)
{
	int *x = (int *) a;
	int *y = (int *) b;
	return *x - *y;
}

double sortAndCompareValues(int* A, int n) {

	qsort (A, n, sizeof(int), comp);

	double start, stop, elapsed;
    start = (double) clock () / CLOCKS_PER_SEC;

    for(unsigned int i=0; i < n; ++i)
	{
		if(A[i] < 5000){
			A[i]++;
		}
	}

	stop = (double) clock () / CLOCKS_PER_SEC;
    elapsed = stop - start;

	return elapsed;
}

double unpredictableIf() {

	double start, stop, elapsed;
    start = (double) clock () / CLOCKS_PER_SEC;

    for(unsigned int i=0; i < 1000000; ++i)
	{
		int x = rand()%1000;
		int y = 200;
		if(x < 500){
			x++;
		}
	}

	stop = (double) clock () / CLOCKS_PER_SEC;
    elapsed = stop - start;

	return elapsed;
}

double predictableIf() {

	double start, stop, elapsed;
    start = (double) clock () / CLOCKS_PER_SEC;

    for(unsigned int i=0; i < 1000000; ++i)
	{
		int x = rand()%1000;
		int y = 200;
		if(y < 500){
			x++;
		}
	}

	stop = (double) clock () / CLOCKS_PER_SEC;
    elapsed = stop - start;

	return elapsed;
}