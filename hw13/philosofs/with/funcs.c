#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 5

//глобалы для вилок
pthread_mutex_t forks[N];

// общий мьютекс и условная переменная
pthread_mutex_t global_mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

// функция философа
void* philosopher(void* arg) {
    int id = *(int*)arg;
    int left = id;
    int right = (id + 1) % N;

    while (1) {
        printf("Философ %d думает\n", id);
        usleep(500000);

        pthread_mutex_lock(&global_mtx);

        // проверяем обе вилки
        if (pthread_mutex_trylock(&forks[left]) == 0) {
            if (pthread_mutex_trylock(&forks[right]) == 0) {
                // успешно взяли обе вилки
                pthread_mutex_unlock(&global_mtx);

                printf("Философ %d ест\n", id);
                usleep(500000);

                // освобождаем вилки
                pthread_mutex_unlock(&forks[right]);
                pthread_mutex_unlock(&forks[left]);

                // сигнал другим философам
                pthread_mutex_lock(&global_mtx);
                pthread_cond_broadcast(&cond);
                pthread_mutex_unlock(&global_mtx);
            } else {
                // правую не удалось — отпускаем левую
                pthread_mutex_unlock(&forks[left]);
                // ждём сигнал
                pthread_cond_wait(&cond, &global_mtx);
                pthread_mutex_unlock(&global_mtx);
            }
        } else {
            // левую не удалось — ждём сигнал
            pthread_cond_wait(&cond, &global_mtx);
            pthread_mutex_unlock(&global_mtx);
        }
    }
    return NULL;
}

