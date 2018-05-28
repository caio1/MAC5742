#include "iofunctions.h"

double ** readMatrix(int64* height, int64* width, char* path){
	FILE *fp;
	fp = fopen(path, "r");
	double ** matrix;

	fscanf(fp, "%llu %llu", height, width);

	matrix = malloc(*height * sizeof(double*));
	for (int64 i = 0; i < *height; i++){
		matrix[i] = calloc(*width, sizeof(double));
	}

	int64 x, y;
	double value;

	while (fscanf(fp, "%llu %llu %lf", &y, &x, &value) != EOF){
		matrix[y-1][x-1] = value;
	}

	return matrix;
}

void saveMatrix(double **M, int64 height, int64 width, char* path){
	FILE *fp;
	fp = fopen(path, "w");

	fprintf(fp, "%llu %llu\n", height, width);

	for (int64 i = 0; i < height; i++)
	{
		for (int64 j = 0; j < width; j++)
		{
			fprintf(fp, "%llu %llu %lf\n", i + 1, j + 1, M[i][j]);
		}
	}
}