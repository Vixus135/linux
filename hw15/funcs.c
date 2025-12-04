#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// глобальные семафоры и счётчики
sem_t semA, semB, semC, semModule, semProduct;
int countA = 0, countB = 0, countC = 0, countModule = 0, countProduct = 0;

// функция изготовления детали A
void* makeA(void* arg) {
    while (1) {
        sleep(1);
        sem_post(&semA);
        countA++;
        printf("Сделана деталь A\n");
    }
    return NULL;
}

// функция изготовления детали B
void* makeB(void* arg) {
    while (1) {
        sleep(2);
        sem_post(&semB);
        countB++;
        printf("Сделана деталь B\n");
    }
    return NULL;
}

// функция изготовления детали C
void* makeC(void* arg) {
    while (1) {
        sleep(3);
        sem_post(&semC);
        countC++;
        printf("Сделана деталь C\n");
    }
    return NULL;
}

// сборка модуля (A+B)
void* module(void* arg) {
    while (1) {
        sem_wait(&semA);
        sem_wait(&semB);
        sem_post(&semModule);
        countModule++;
        printf("Собран модуль (A+B)\n");
    }
    return NULL;
}

// сборка изделия (Module+C)
void* product(void* arg) {
    while (1) {
        sem_wait(&semModule);
        sem_wait(&semC);
        sem_post(&semProduct);
        countProduct++;
        printf("Собрано изделие (Module+C)\n");
    }
    return NULL;
}

// обработчик Ctrl+C
void handler(int sig) {
    printf("\n=== Итоговая статистика ===\n");
    printf("Деталей A: %d\n", countA);
    printf("Деталей B: %d\n", countB);
    printf("Деталей C: %d\n", countC);
    printf("Модулей:   %d\n", countModule);
    printf("Изделий:   %d\n", countProduct);
    exit(0);
}
