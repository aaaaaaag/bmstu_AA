#ifndef __PRINT_MATRIX__
#define __PRINT_MATRIX__

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "thread_structs.h"

#define N 1024
#define M N

void print_matrix(int **matrix);

void print_matrix(double **matrix);

args_t *create_args(int n, int m, int read_file);

void base_geometric_mean(args_t *args);

void *parallel_geometric_mean_by_columns(void *args);


#endif
