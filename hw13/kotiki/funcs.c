#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// глобалы
int food = 500; // стартовое количество корма
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

// функция владельца: подсыпает корм, если его мало
void* owner(void* arg) {
    while (1) {
        pthread_mutex_lock(&mtx);
        if (food < 100) {
            food += 500;
            if (food > 1000) food = 1000;
            printf("Хозяин подсыпал корм, теперь %d г\n", food);
            pthread_cond_broadcast(&cond); // уведомляем котов
        }
        pthread_mutex_unlock(&mtx);
        sleep(2); // пауза
    }
    return NULL;
}

// функция кота
void* cat(void* arg) {
    int id = *(int*)arg;
    while (1) {
        pthread_mutex_lock(&mtx);
        while (food < 100) pthread_cond_wait(&cond, &mtx); // ждём пока хозяин подсыпет
        food -= 100;
        printf("Кот %d поел, осталось %d г в миске\n", id, food);
        pthread_mutex_unlock(&mtx);
        sleep(1); // пауза
    }
    return NULL;
}

