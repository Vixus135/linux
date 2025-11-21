#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 3

// объявляем внешние переменные (определены в funcs.c)
extern pthread_mutex_t list_mu;
extern pthread_cond_t req;
extern int num_req;
extern struct request* reqs;
extern struct request* lst_req;

// объявляем функции из funcs.c
void add_request(int rqst_num);
void* reqs_loop(void* arg);

int main() {
    pthread_t thrds[NUM_THREADS]; // массив идентификаторов потоков
    int thrd_ids[NUM_THREADS]; // массив ID потоков

    // создаем потоки-обработчики
    for (int i = 0; i < NUM_THREADS; i++) {
        thrd_ids[i] = i;  // присваиваем ID потоку
        // сщздаём поток
        pthread_create(&thrds[i], NULL, reqs_loop, &thrd_ids[i]);
    }
    // генерируем запросы
    for (int i = 0; i < 10; i++) {
        add_request(i);
        sleep(1);  // пауза между запросами
    }
    // даем время на обработку оставшихся запросов
    sleep(3);
    printf("Все запросы обработаны!\n");
    return 0;
}
