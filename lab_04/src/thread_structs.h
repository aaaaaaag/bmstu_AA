#ifndef __THREAD_STRUCTS_H__
#define __THREAD_STRUCTS_H__

#include <stdint.h>

typedef struct {
    int **m1;
    double **res;
} args_t;

typedef struct {
    args_t *matrix_container;
    int thread_id;
    int matrix_size;
    int cnt_threads;
} pthread_args_t;

#endif
