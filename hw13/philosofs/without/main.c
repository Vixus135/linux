#include <stdio.h>
#include <pthread.h>

// глобалы и функцию из funcs.c
extern pthread_mutex_t forks[];
extern void* philosopher(void* arg);

#define N 5

int main() {
    pthread_t ph[N];
    int ids[N];

    // инициализация вилок
    for (int i = 0; i < N; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // создание потоков философов
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&ph[i], NULL, philosopher, &ids[i]);
    }

    // ожидание завершения (бесконечно)
    for (int i = 0; i < N; i++) {
        pthread_join(ph[i], NULL);
    }

    return 0;
}

