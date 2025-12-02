#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

//глобалы из funcs.c
extern pthread_mutex_t mtx;
extern pthread_cond_t barberCond;
extern pthread_cond_t customerCond;
extern int waiting;

void* barber(void* arg);
void* customer(void* arg);

int main() {
    pthread_t b;
    pthread_create(&b, NULL, barber, NULL);

    // запуск 10 клиентов
    for (int i = 1; i <= 10; i++) {
        pthread_t c;
        pthread_create(&c, NULL, customer, &i);
        sleep(1); // клиенты приходят с паузой
    }

    pthread_join(b, NULL);
    return 0;
}

