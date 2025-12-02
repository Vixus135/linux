#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define CHAIRS 3

// глобалы
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t barberCond = PTHREAD_COND_INITIALIZER;
pthread_cond_t customerCond = PTHREAD_COND_INITIALIZER;
int waiting = 0;

// функция парикмахера
void* barber(void* arg) {
    while (1) {
        pthread_mutex_lock(&mtx);
        while (waiting == 0) {
            printf("Парикмахер спит\n");
            pthread_cond_wait(&barberCond, &mtx);
        }
        waiting--;
        printf("Парикмахер стрижёт клиента, осталось %d\n", waiting);
        pthread_mutex_unlock(&mtx);

        sleep(2); // идёт стрижка

        pthread_cond_signal(&customerCond); // увед клиента
    }
    return NULL;
}

// функция клиента
void* customer(void* arg) {
    int id = *(int*)arg;
    pthread_mutex_lock(&mtx);
    if (waiting < CHAIRS) {
        waiting++;
        printf("Клиент %d ждёт\n", id);
        pthread_cond_signal(&barberCond);
        pthread_mutex_unlock(&mtx);

        pthread_mutex_lock(&mtx);
        pthread_cond_wait(&customerCond, &mtx);
        printf("Клиент %d теперь подстрижен\n", id);
        pthread_mutex_unlock(&mtx);
    } else {
        printf("Клиент %d ушёл — нет мест\n", id);
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

