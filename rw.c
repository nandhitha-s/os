#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define NUM_READERS 3
#define NUM_WRITERS 2

sem_t mutex, wrt;
int read_count = 0;
int data = 0;
pthread_mutex_t data_mutex = PTHREAD_MUTEX_INITIALIZER;

void *reader(void *arg) {
    int reader_id = *(int *)arg;

    while (1) {

        sem_wait(&mutex);
        read_count++;


        if (read_count == 1) {
            sem_wait(&wrt);
        }

        sem_post(&mutex);


        pthread_mutex_lock(&data_mutex);
        int current_data = data;
        pthread_mutex_unlock(&data_mutex);
        printf("Reader %d read data: %d\n", reader_id, current_data);

        sem_wait(&mutex);
        read_count--;


        if (read_count == 0) {
            sem_post(&wrt);
        }

        sem_post(&mutex);


        sleep(1);
    }
}

void *writer(void *arg) {
    int writer_id = *(int *)arg;

    while (1) {

        sem_wait(&wrt);


        pthread_mutex_lock(&data_mutex);
        data++;
        int current_data = data;
        pthread_mutex_unlock(&data_mutex);
        printf("Writer %d wrote data: %d\n", writer_id, current_data);


        sem_post(&wrt);


        sleep(2);
    }
}

int main() {
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    pthread_t readers[NUM_READERS];
    pthread_t writers[NUM_WRITERS];

    int reader_ids[NUM_READERS];
    int writer_ids[NUM_WRITERS];

    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}