#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#define S 3
#define NUM_STUDENTS 8
sem_t pizza;
sem_t deliver;
int num_slices=0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void study(void *arg)
{
    long student_id=(long)arg;
    printf("student %ld has taken a slice and is studying.\n",student_id);
    sleep(1);
}
void *student(void *arg)
{
    while(1)
    {
        sem_wait(&pizza);
        pthread_mutex_lock(&mutex);
        num_slices--;
        if(num_slices==0)
        {
            sem_post(&deliver);
        }
        study(arg);
        pthread_mutex_unlock(&mutex);
    }
}
void make_pizza()
{
    printf("delivery thread is making pizza.\n");
    sleep(2);
}
void *delivery_thread(void *arg)
{
    while(1)
    {
        sem_wait(&deliver);
        make_pizza();
        pthread_mutex_lock(&mutex);
        num_slices=S;
        pthread_mutex_unlock(&mutex);
        printf("delivery pizza\n");
        for(int i=0;i<S;i++)
        {
            sem_post(&pizza);
        }
    }
}
int main()
{
    sem_init(&pizza,0,0);
    sem_init(&deliver,0,1);
    pthread_t student_tids[NUM_STUDENTS];
    pthread_t delivery_tid;
    for(int i=0;i<NUM_STUDENTS;i++)
    {
        if(pthread_create(&student_tids[i],NULL,student,(void *)i)!=0)
        {
            perror("pthread create");
            return 1;
        }
    }
    if(pthread_create(&delivery_tid,NULL,delivery_thread,NULL)!=0)
    {
        perror("pthread create");
        return 1;
    }
    for(int i=0;i<NUM_STUDENTS;i++)
    {
        if(pthread_join(student_tids[i],NULL)!=0)
        {
            perror("pthread_join");
            return 1;
        }
    }
}