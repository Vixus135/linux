#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 5

// глоб массив мьютексов (вилки)
pthread_mutex_t forks[N];

// функция философа
void* philosopher(void* arg) {
    int id = *(int*)arg;
    while (1) {
        printf("Философ %d думает\n", id);
        usleep(500000); // пауза для "размышлений"

        // чёт философы берут сначала левую, потом правую вилку
        if (id % 2 == 0) {
            pthread_mutex_lock(&forks[id]);
            pthread_mutex_lock(&forks[(id+1)%N]);
        } else {
            // нечёт — наоборот
            pthread_mutex_lock(&forks[(id+1)%N]);
            pthread_mutex_lock(&forks[id]);
        }

        printf("Философ %d ест\n", id);
        usleep(500000); // пауза для "еды"

        // освобождаем вилки
        pthread_mutex_unlock(&forks[id]);
        pthread_mutex_unlock(&forks[(id+1)%N]);
    }
    return NULL;
}

