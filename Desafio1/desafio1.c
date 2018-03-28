#include <functions.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main() {
	int n = 9000000;

	int *A; 
	A = malloc (n * sizeof (int));

	srand(time(NULL));

	for(unsigned int i=0; i < n; ++i)
	{
		A[i] = rand()%10000;
	}

	double t3 = predictableIf();

	double t4 = unpredictableIf();

	double t1 = sortAndCompareValues(A, n);

	double t2 = compareValues(A, n);

    printf("Tempo de execucao sortAndCompare: %f\n", t1);
    printf("Tempo de execucao compare:        %f\n", t2);
    printf("Tempo de execucao predictableIf:  %f\n", t3);
    printf("Tempo de execucao unpredictableIf:%f\n", t4);

	free(A);

  return(0);
}