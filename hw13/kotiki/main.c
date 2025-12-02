#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//глобалы из funcs.c
extern int food;
extern pthread_mutex_t mtx;
extern pthread_cond_t cond;

void* owner(void* arg);
void* cat(void* arg);

int main() {
    pthread_t owner_t, cats[5];
    int ids[5];

    // создаём поток хозяина
    pthread_create(&owner_t, NULL, owner, NULL);

    // создаём 5 потоков котов
    for (int i = 0; i < 5; i++) {
        ids[i] = i + 1;
        pthread_create(&cats[i], NULL, cat, &ids[i]);
    }

    // ждём завершения потока хозяина (он бесконечный)
    pthread_join(owner_t, NULL);
    return 0;
}

