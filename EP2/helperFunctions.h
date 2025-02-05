#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <pthread.h>
#include <limits.h>
#include <omp.h>

#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#define MATRIX_WIDTH 3
#define MATRIX_SIZE 9

#ifdef DEBUG
#endif

int min(int a, int b);
int *generateRandomMatrix(int height, int width);
void printMatrix(int *M, int height, int width);
void freeMatrixList(int **matrixList, int matrixAmount);
void generateRandomInputFile(int matrixAmount, char *path);
int compareResults(int *sequential, int *gpu);
int nextPowerOfTwo(int n);

#endif
