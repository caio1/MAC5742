#include "functions.h"

#ifndef IOFUNCTIONS_H
#define IOFUNCTIONS_H

double ** readMatrix(int64* height, int64* width, char* path);
double **readMatrixColumnWise(int64 *height, int64 *width, char *path);
void saveMatrix(double **M, int64 height, int64 width, char* path);

#endif
