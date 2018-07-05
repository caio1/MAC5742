#include "helperFunctions.h"

#ifndef IOFUNCTIONS_H
#define IOFUNCTIONS_H

void calculate_f_sequential();
void *calculate_f_pthreads(void *args);
void calculate_f_CPU();

#endif
