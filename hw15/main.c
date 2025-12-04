#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
// глобалы и функции из funcs.c
extern sem_t semA, semB, semC, semModule, semProduct;
extern int countA, countB, countC, countModule, countProduct;
void* makeA(void* arg);
void* makeB(void* arg);
void* makeC(void* arg);
void* module(void* arg);
void* product(void* arg);
void handler(int sig);

int main() {
    pthread_t tA, tB, tC, tM, tP;

    // инициализация семафоров
    sem_init(&semA, 0, 0);
    sem_init(&semB, 0, 0);
    sem_init(&semC, 0, 0);
    sem_init(&semModule, 0, 0);
    sem_init(&semProduct, 0, 0);

    // установка обработчика Ctrl+C
    signal(SIGINT, handler);

    // создание потоков
    pthread_create(&tA, NULL, makeA, NULL);
    pthread_create(&tB, NULL, makeB, NULL);
    pthread_create(&tC, NULL, makeC, NULL);
    pthread_create(&tM, NULL, module, NULL);
    pthread_create(&tP, NULL, product, NULL);

    // ожидание завершения (бесконечно)
    pthread_join(tP, NULL);

    return 0;
}

