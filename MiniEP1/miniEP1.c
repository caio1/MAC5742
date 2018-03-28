#include <sumMatrices.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
	int m = 9000;
	int n = 9000;

	int **M; 
	M = malloc (m * sizeof (int *));
	for (int i = 0; i < m; ++i)
		M[i] = malloc (n * sizeof (int));

	double t2 = sumValueRowWise(M, n, m);

	double t1 = sumValueColumnWise(M, n, m);

    printf("Tempo de execucao columnWise: %f\n", t1);
    printf("Tempo de execucao rowWise:    %f\n", t2);

    for (int i = 0; i < m; ++i)
		free(M[i]);
	free(M);

  return(0);
}