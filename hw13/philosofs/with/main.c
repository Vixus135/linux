#include <stdio.h>
#include <pthread.h>

// переменные и функцию из funcs
extern pthread_mutex_t forks[];
extern pthread_mutex_t global_mtx;
extern pthread_cond_t cond;

void* philosopher(void* arg);

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

    // ждём (бесконечно)
    for (int i = 0; i < N; i++) {
        pthread_join(ph[i], NULL);
    }

    return 0;
}

