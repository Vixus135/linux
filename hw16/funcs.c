#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_MSG 10      // максимум сообщений в очереди
#define MSG_SIZE 80     // максимум символов в сообщении

typedef struct {
    char msgs[MAX_MSG][MSG_SIZE];
    int head, tail;
} queue;

// глобалы
queue q;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
sem_t semEmpty, semFull;
int dropped = 0;

// инициализация
void mymsginit(queue *qq) {
    qq->head = qq->tail = 0;
    sem_init(&semEmpty, 0, MAX_MSG);
    sem_init(&semFull, 0, 0);
}

//завершение работы
void mymsgdrop(queue *qq) {
    dropped = 1;
    sem_post(&semEmpty);
    sem_post(&semFull);
}

// уничтожение
void mymsgdestroy(queue *qq) {
    sem_destroy(&semEmpty);
    sem_destroy(&semFull);
}

// "положить" сообщение
int mymsgput(queue *qq, char *msg) {
    if (dropped) return 0;
    sem_wait(&semEmpty);
    if (dropped) return 0;

    pthread_mutex_lock(&mtx);
    strncpy(qq->msgs[qq->tail], msg, MSG_SIZE-1);
    qq->msgs[qq->tail][MSG_SIZE-1] = '\0';
    qq->tail = (qq->tail + 1) % MAX_MSG;
    pthread_mutex_unlock(&mtx);

    sem_post(&semFull);
    return strlen(msg);
}

// взять сообщение
int mymsgget(queue *qq, char *buf, size_t bufsize) {
    if (dropped) return 0;
    sem_wait(&semFull);
    if (dropped) return 0;

    pthread_mutex_lock(&mtx);
    strncpy(buf, qq->msgs[qq->head], bufsize-1);
    buf[bufsize-1] = '\0';
    qq->head = (qq->head + 1) % MAX_MSG;
    pthread_mutex_unlock(&mtx);

    sem_post(&semEmpty);
    return strlen(buf);
}

// производитель
void* producer(void* arg) {
    int id = *(int*)arg;
    char msg[MSG_SIZE];
    for (int i=0; i<5; i++) {
        sprintf(msg, "Producer %d: message %d", id, i);
        mymsgput(&q, msg);
        printf("[Producer %d] put: %s\n", id, msg);
    }
    return NULL;
}

// потребитель
void* consumer(void* arg) {
    int id = *(int*)arg;
    char buf[MSG_SIZE];
    for (int i=0; i<5; i++) {
        mymsgget(&q, buf, sizeof(buf));
        printf("[Consumer %d] got: %s\n", id, buf);
    }
    return NULL;
}

