#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_CAPACITY 5

sem_t rope_mutex, left_mutex, right_mutex;
int left_count = 0, right_count = 0;

struct BaboonInfo {
    int baboon_num;
    int arrival_time;
};

void* cross_rope(void* arg) {
    struct BaboonInfo* baboon_info = (struct BaboonInfo*)arg;
    int baboon_num = baboon_info->baboon_num;
    int arrival_time = baboon_info->arrival_time;
    int side = (baboon_num % 2 == 0) ? 0 : 1;
    printf("Baboon %d arrived at time %d and is initially on the %s side.\n", baboon_num, arrival_time, (side == 0 ? "left" : "right"));

    if (side == 0) {
        sem_wait(&left_mutex);
        if (++left_count == 1)
            sem_wait(&rope_mutex);
        sem_post(&left_mutex);
    } else {
        sem_wait(&right_mutex);
        if (++right_count == 1)
            sem_wait(&rope_mutex);
        sem_post(&right_mutex);
    }

    printf("Baboon %d is crossing from %s to %s\n", baboon_num, (side == 0 ? "left" : "right"), (side == 0 ? "right" : "left"));

    sleep(1);
    if (side == 0) {
        sem_wait(&left_mutex);
        if (--left_count == 0)
            sem_post(&rope_mutex);
        sem_post(&left_mutex);
    } else {
        sem_wait(&right_mutex);
        if (--right_count == 0)
            sem_post(&rope_mutex);
        sem_post(&right_mutex);
    }

    printf("Baboon %d has crossed.\n", baboon_num);

    return NULL;
}

int main() {
    pthread_t threads[10];
    struct BaboonInfo baboon_infos[10] = {
        {1, 0}, {2, 1}, {3, 2}, {4, 3}, {5, 4}, {6, 5}, {7, 6}, {8, 7}, {9, 8}, {10, 9}
    };
    sem_init(&rope_mutex, 0, 1);
    sem_init(&left_mutex, 0, 1);
    sem_init(&right_mutex, 0, 1);

    for (int i = 0; i < 10; i++) {
        pthread_create(&threads[i], NULL, cross_rope, &baboon_infos[i]);
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&rope_mutex);
    sem_destroy(&left_mutex);
    sem_destroy(&right_mutex);

    return 0;
}
