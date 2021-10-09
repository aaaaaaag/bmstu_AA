#include "threads.h"
#include <pthread.h>

int start_threading(args_t *args, const int cnt_threads, const int type) {
    pthread_t *threads = (pthread_t *)malloc(cnt_threads * sizeof(pthread_t));

    if (!threads) {
        fprintf(stderr, "Ошибка при выделении памяти. Файл: %s\nСтрока: %d\n", __FILE__, __LINE__);
        return ALLOCATE_ERROR;
    }

    pthread_args_t *args_array = (pthread_args_t *)malloc(sizeof(pthread_args_t) * cnt_threads);

    if (!args_array) {
        free(threads);
        fprintf(stderr, "Ошибка при выделении памяти: %d\nФайл: %s\n", __LINE__, __FILE__);
        return ALLOCATE_ERROR;
    }

    for (int i = 0; i < cnt_threads; i++) {
        args_array[i].matrix_container = args;
        args_array[i].thread_id = i;
        args_array[i].matrix_size = N;
        args_array[i].cnt_threads = cnt_threads;

        switch (type) {
            case 1:
                pthread_create(&threads[i], NULL, parallel_geometric_mean_by_columns, &args_array[i]);
                break;
        }
    }

    for (int i = 0; i < cnt_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    free(args_array);
    free(threads);

    return OK;
}
