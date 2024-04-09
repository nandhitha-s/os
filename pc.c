#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

#define buffer 10
int buf[buffer];
pthread_mutex_t mutex;
sem_t full,empty;
int count = 0;
pthread_t p[100],c[100];

void ini()
{
    pthread_mutex_init(&mutex,NULL);
    sem_init(&full,0,0);
    sem_init(&empty,0,buffer);
}
void write(int item)
{
    buf[count++]=item;
}
int read()
{
    return buf[--count];
}

void *producer(void *arg)
{
    int waiting,item;
    while(1)
    {
        item = rand()%6;
        waiting = rand()%5;
        sleep(waiting);
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        printf("Produced : %d\n",item);
        write(item);
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

void *consum(void *arg)
{
    int item;
    while (1)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        item = read();
        printf("consumed : %d\n",item);
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }

}

int main()
{
    int n1,n2;
    printf("Enter the no of producer : ");
    scanf("%d",&n1);
    printf("Enter the no of consumer : ");
    scanf("%d",&n2);
    ini();
    for(int i =0;i<n1;i++)
    {
        pthread_create(&p[i],NULL,producer,NULL);
    }
    for(int i=0;i<n2;i++)
    {
        pthread_create(&c[i],NULL,consum,NULL);
    }
    for(int i =0 ;i<n1;i++)
    {
        pthread_join(p[i],NULL);
    }
    for(int i =0;i<n2;i++)
    {
        pthread_join(c[i],NULL);
    }

    return 0;
}