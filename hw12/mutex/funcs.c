#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 3

// разделяем мьютексы по ответственности
pthread_mutex_t list_mu = PTHREAD_MUTEX_INITIALIZER;  // мьютекс для списка запросов
pthread_cond_t req = PTHREAD_COND_INITIALIZER;

int num_req = 0; // счётчик

// структуриркем запрос
struct request {
    int num;
    struct request* next; // указатель на след запрос
};

struct request* reqs = NULL; // голова списка
struct request* lst_req = NULL; // хвост списка

// добавляем запрос (используем list_mu)
void add_request(int rqst_num) {
    pthread_mutex_lock(&list_mu); // блокаем мьютекс,чтобы безопасно перейти к списку

    // создаем новый запрос
    struct request* new_req = malloc(sizeof(struct request));
    new_req->num = rqst_num;
    new_req->next = NULL;

    // добавляем его в конец списка
    if (lst_req == NULL) {
        reqs = new_req; // если список пустой, то запрос первый и последний
    } else {
        lst_req->next = new_req; // иначе добавляем после последнего
    }
    lst_req = new_req;
    num_req++;
    printf("Добавлен запрос %d\n", rqst_num);
    // разблокаем мьютекс
    pthread_mutex_unlock(&list_mu);
    // оповещаем о новом запросе
    pthread_cond_signal(&req);
}

// получаем запрос (используем list_mu)
struct request* get_rqst() {
    pthread_mutex_lock(&list_mu);
    struct request* req = NULL;
    if (num_req > 0) {
        // если есть запросы берем первый из списка
        req = reqs;
        // перемещаем голову на следующий запрос
        reqs = reqs->next;
        // если список пуст обнуляем указатель на последний запрос
        if (reqs == NULL) {
            lst_req = NULL;
        }
        num_req--;
    }
    // разблокаем мьютекс
    pthread_mutex_unlock(&list_mu);
    return req;
}

// обрабатываем запрос
void handle_rqst(struct request* req, int thre_id) {
    if (req) {
        printf("Поток %d обработал запрос %d\n", thre_id, req->num);
        free(req);
    }
}

// главный цикл обработки
void* reqs_loop(void* arg) {
    int thre_id = *(int*)arg;

    while (1) {
        // попытка взять запрос
        struct request* req = get_rqst();

        if (req != NULL) {
            // если есть запрос - обрабатываем
            handle_rqst(req, thre_id);
        } else {
            // если нету - ждем
            pthread_mutex_lock(&list_mu);
            while (num_req == 0) {
                pthread_cond_wait(&req, &list_mu);
            }
            pthread_mutex_unlock(&list_mu);
        }
    }
    return NULL;
}

