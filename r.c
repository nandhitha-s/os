#include<stdio.h>

#include<stdlib.h>

#include<pthread.h>

#include<semaphore.h>



#define MAX 6

#define N 3



sem_t entering_diner,enter_done,exiting_diner,exit_done;

sem_t mutex_enter,mutex_exit;

int count_enter = 0;

int count_exit = 0;

int c = 0;



void* diner_thread(void* args){



        sem_wait(&entering_diner);      /* Waits for the Front Door to open*/

        printf("Entering Diners \n");

        sem_wait(&mutex_enter);

        count_enter++;

        c++;

        printf("Count Enter : %d\n",count_enter);

        if(count_enter != N)

                sem_post(&entering_diner);

        else

                sem_post(&enter_done);

        sem_post(&mutex_enter);



        sem_wait(&exiting_diner);

        printf("\nEat\n");

        sem_post(&exiting_diner);



        sem_wait(&mutex_exit);

        //printf("Count : %d %d\n",count_exit,count_exit==N);

        count_exit++;

        if((count_exit) == N)

                sem_post(&exit_done);

        sem_post(&mutex_exit);

}



void* restaurant_thread(void* args){



        while(1){



                printf("Front Door Opened!\n");

                sem_post(&entering_diner);

                if (c==MAX){

                        printf("Front Door Closed\n");

                        /*sem_post(&enter_done);

                        sem_post(&exiting_diner);

                        sem_post(&exit_done);

                        */break;

                }

                sem_wait(&enter_done);

                printf("Front Door Closed\n");







                printf("Serving Food\n");

                printf("Back Door Opened!\n");

                sem_post(&exiting_diner);



                sem_wait(&exit_done);

                sem_wait(&exiting_diner);

                sem_wait(&mutex_exit);

                printf("Count Exit : %d\n",count_enter);

                sem_post(&mutex_exit);

                printf("\nBack Door Closed!\n");



                sem_wait(&mutex_exit);

                count_exit = 0;

                printf("Setting Count_Exit to %d\n",count_exit);

                sem_post(&mutex_exit);



                sem_wait(&mutex_enter);

                count_enter = 0;

                printf("Setting Count_Enter to %d\n",count_exit);

                sem_post(&mutex_enter);

        }

}





int main(){



        sem_init(&entering_diner,0,0);

        sem_init(&enter_done,0,0);

        sem_init(&exiting_diner,0,0);

        sem_init(&exit_done,0,0);



        sem_init(&mutex_enter,0,1);

        sem_init(&mutex_exit,0,1);



        pthread_t diners[MAX];

        pthread_t restaurant;



        for(int i=0;i<MAX;i++)

                pthread_create(&diners[i],NULL,diner_thread,NULL);



        pthread_create(&restaurant,NULL,restaurant_thread,NULL);



        for(int i=0;i<MAX;i++)

                pthread_join(diners[i],NULL);

        pthread_join(restaurant,NULL);



}