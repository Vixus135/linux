#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int msg_cnt = 0;  // счетчик сообщений

void* handler(void* arg);
void* sender(void* arg);

int main() {
    pthread_t hnd, snd;
    // сосздадим  потоки
    pthread_create(&hnd, NULL, handler, NULL);
    pthread_create(&snd, NULL, sender, NULL);
    // ожидаем
    pthread_join(hnd, NULL);
    pthread_join(snd, NULL);
    return 0;
}
