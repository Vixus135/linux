#include <stdio.h>
#include <pthread.h>

#define MAX_MSG 10
#define MSG_SIZE 80

typedef struct {
    char msgs[MAX_MSG][MSG_SIZE];
    int head, tail;
} queue;

// глобалы и функции из funcs.c
extern queue q;
void mymsginit(queue *qq);
void mymsgdrop(queue *qq);
void mymsgdestroy(queue *qq);
void* producer(void* arg);
void* consumer(void* arg);

int main() {
    pthread_t prod[2], cons[2];
    int ids[2] = {1,2};

    mymsginit(&q);

    // запускаем 2 производителя и 2 потребителя
    pthread_create(&prod[0], NULL, producer, &ids[0]);
    pthread_create(&prod[1], NULL, producer, &ids[1]);
    pthread_create(&cons[0], NULL, consumer, &ids[0]);
    pthread_create(&cons[1], NULL, consumer, &ids[1]);

    // ждём завершения
    for (int i=0; i<2; i++) {
        pthread_join(prod[i], NULL);
        pthread_join(cons[i], NULL);
    }

    mymsgdrop(&q);
    mymsgdestroy(&q);
    return 0;
}


