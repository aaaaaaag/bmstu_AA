#include "geometric_mean.h"
#include "malloc.h"
#include "cmath"

void print_matrix(int **matrix) {
    fprintf(stdout, "Результат: \n");

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void print_matrix(double **matrix) {
    fprintf(stdout, "Результат: \n");

    for (int i = 0; i < 1; i++) {
        for (int j = 0; j < M; j++) {
            printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }
}

static void read_matrix(int **matrix, FILE *file) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }
}

static void init_matrix(int **matrix) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            matrix[i][j] = (i*2 + j*3) % 100 + 1;
        }
    }
}

static double **create_matrix_double(int n, int m) {
    double **matrix = (double **)malloc(sizeof(double *) * n);

    if (!matrix) {
        fprintf(stderr, "Ошибка при выделении памяти. Файл: %s\nСтрока: %d\n", __FILE__, __LINE__);
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        *(matrix + i) = (double *)malloc(sizeof(double ) * m);

        if (!(*(matrix + i))) {
            fprintf(stderr, "Ошибка при выделении памяти. Файл: %s\nСтрока: %d\n", __FILE__, __LINE__);
            return NULL;
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            matrix[i][j] = 1;
    }

    return matrix;
}

static int **create_matrix(int n, int m) {
    int **matrix = (int **)malloc(sizeof(int *) * n);

    if (!matrix) {
        fprintf(stderr, "Ошибка при выделении памяти. Файл: %s\nСтрока: %d\n", __FILE__, __LINE__);
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        *(matrix + i) = (int *)malloc(sizeof(int) * m);

        if (!(*(matrix + i))) {
            fprintf(stderr, "Ошибка при выделении памяти. Файл: %s\nСтрока: %d\n", __FILE__, __LINE__);
            return NULL;
        }
    }

    return matrix;
}

args_t *create_args(int n, int m, int read_file) {
    args_t *args = (args_t *)malloc(sizeof(args));
    if (!args) {
        return NULL;
    }

    if (!(args->m1 = create_matrix(n, m))) {
        return NULL; // TODO: free
    }

    if (read_file) {
        FILE *mtr_file = fopen("data/matrix1.txt", "r");

        if (!mtr_file) {
            fprintf(stderr, "Ошибка при открытии файла. Файл: %s\nСтрока: %d\n", __FILE__, __LINE__);
            return NULL; // TODO: free
        }

        read_matrix(args->m1, mtr_file);
        fclose(mtr_file);
    } else {
        init_matrix(args->m1);
    }
    if (!(args->res = create_matrix_double(N / 10 + 2, m))) {
        return NULL; // TODO: free
    }

    return args;
}

void base_geometric_mean(args_t *args) {

    for (int j = 0; j < M; j++) {
        int ind_tmp_val = 1;
        bool flag = true;
        double n = N;
        for (int i = 0; i < N; i++) {
            args->res[ind_tmp_val][j] *= args->m1[i][j];
            if (i % 10 == 0 && i != 0) {
                flag = false;
                args->res[ind_tmp_val][j] = pow(args->res[ind_tmp_val][j], static_cast<double>(1) / n);
                ind_tmp_val++;
            }
        }
        if (flag)
            args->res[ind_tmp_val][j] = pow(args->res[ind_tmp_val][j], static_cast<double>(1) / n);
        for (int ind = 1; ind < N / 10 + 2; ind++)
            args->res[0][j] *= args->res[ind][j];
    }
}

void *parallel_geometric_mean_by_columns(void *args) {
    pthread_args_t *all_data = (pthread_args_t *)args;

    int col_start = all_data->thread_id * (all_data->matrix_size / all_data->cnt_threads);
    int col_end = (all_data->thread_id + 1) * (all_data->matrix_size / all_data->cnt_threads);

    for (int j = col_start; j < col_end; j++) {
        int ind_tmp_val = 1;
        for (int i = 0; i < N; i++) {
            all_data->matrix_container->res[ind_tmp_val][j] *= all_data->matrix_container->m1[i][j];
            if (i % 10 == 0 && i != 0) {
                double n = N;
                all_data->matrix_container->res[ind_tmp_val][j] =
                        pow(all_data->matrix_container->res[ind_tmp_val][j], static_cast<double>(1) / n);
                ind_tmp_val++;
            }
        }
        for (int ind = 1; ind < N / 10 + 2; ind++)
            all_data->matrix_container->res[0][j] *= all_data->matrix_container->res[ind][j];
    }
    return NULL;
}