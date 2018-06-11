#include "helperFunctions.h"

#ifndef IOFUNCTIONS_H
#define IOFUNCTIONS_H

int **readMatrices(int* matrixAmount, char *path);
void saveMatrix(int **matrixList, int matrixAmount, char *path);

#endif
