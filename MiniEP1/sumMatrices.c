#include <sumMatrices.h>
#include <stdio.h>
#include <time.h>


double sumValueRowWise(int** M, int width, int height) {

	double start, stop, elapsed;
    start = (double) clock () / CLOCKS_PER_SEC;

	for(unsigned int y=0; y<height; ++y)
	{
	    for(unsigned int x=0; x<width; ++x)
	    {
	        M[y][x] += 1;
	    }
	}

	stop = (double) clock () / CLOCKS_PER_SEC;
    elapsed = stop - start;

	return elapsed;
}

double sumValueColumnWise(int** M, int width, int height) {

	double start, stop, elapsed;
    start = (double) clock () / CLOCKS_PER_SEC;

	for(unsigned int x=0; x<width; ++x)
	{
		for(unsigned int y=0; y<height; ++y)
	    {
	        M[y][x] += 1;
	    }
	}

	stop = (double) clock () / CLOCKS_PER_SEC;
    elapsed = stop - start;

	return elapsed;
}