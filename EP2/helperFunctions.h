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


int min(int a, int b);
int *generateRandomMatrix(int height, int width);
void printMatrix(int *M, int height, int width);
void freeMatrixList(int **matrixList, int matrixAmount);
void generateRandomInputFile(int matrixAmount);

#endif
