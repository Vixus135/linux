#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int msg_cnt = 0;  // счетчик сообщений

// функция обработчика
void* handler(void* arg) {
    while (1) {
        pthread_mutex_lock(&mtx);
        // ждем сообщения
        while (msg_cnt == 0) {
            pthread_cond_wait(&cond, &mtx);
        }
        // обрабатываем
        printf("Обработано. Осталось: %d\n", msg_cnt);
        msg_cnt--;
        pthread_mutex_unlock(&mtx);
        sleep(1);
    }
    return NULL;
}

// функция отправителя
void* sender(void* arg) {
    int cnt = 0;
    while (1) {
        sleep(rand() % 3 + 1);  // пауза 1-3 сек
        pthread_mutex_lock(&mtx);
        msg_cnt++;
        cnt++;
        printf("Отправлено %d\n", cnt);
        // пробуждаем обработчик
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}
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
