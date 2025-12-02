#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// определим глобальные переменные
int number;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

//поток-ген: каждую секунду создаёт случайное число
void* generator(void* arg) {
    while (1) {
        sleep(1);
        pthread_mutex_lock(&mtx);
        number = rand() % 100;
        printf("Сгенерировано: %d\n", number);
        pthread_cond_broadcast(&cond); // уведомляем все потоки о сгенерированном числе
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}
//поток для вычисления квадрата (чёт числа)
void* square(void* arg) {
    while (1) {
        pthread_mutex_lock(&mtx);
        pthread_cond_wait(&cond, &mtx); // ждём сигнал
        if (number % 2 == 0)
            printf("Квадрат: %d\n", number * number);
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}
//поток для вычисления куба (нечёт числа)
void* cube(void* arg) {
    while (1) {
        pthread_mutex_lock(&mtx);
        pthread_cond_wait(&cond, &mtx); // ждём сигнал
        if (number % 2 == 1)
            printf("Куб: %d\n", number * number * number);
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}
