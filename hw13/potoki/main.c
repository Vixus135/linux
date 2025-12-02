#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

// объявляем глобальные переменные и функции из funcs.c
extern int number;
extern pthread_mutex_t mtx;
extern pthread_cond_t cond;

void* generator(void* arg);
void* square(void* arg);
void* cube(void* arg);

int main() {
    pthread_t t1, t2, t3; // идентификаторы потоков
    srand(time(NULL));    // инициализация генератора случайных чисел

    // создаём три потока
    pthread_create(&t1, NULL, generator, NULL);
    pthread_create(&t2, NULL, square, NULL);
    pthread_create(&t3, NULL, cube, NULL);

    // ждём завершения генератора (он бесконечный)
    pthread_join(t1, NULL);
    return 0;
}

