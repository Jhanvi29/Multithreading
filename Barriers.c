#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <semaphore.h>

#define thread_num 16
sem_t semaphore;

void* routine(void* args){
    int val = *(int*)args;
    printf("Waiting to login %d \n" , val);
    sem_wait(&semaphore);
    sleep(rand() % 5 + 1);
    printf("In the server %d \n" , val);

    sem_post(&semaphore);
    printf("Logging out %d \n" , val);
    return 0;
}

int main(int args, char* argv[]){
    
    pthread_t th[thread_num];
    sem_init(&semaphore, 0, 4);

    for(int i=0; i<thread_num; i++){
        int* a = malloc(sizeof(int));
        *a = i;
        pthread_create(&th[i] , NULL, &routine, a);
    }

    for(int i=0; i<thread_num; i++){
        pthread_join(th[i] , NULL);
    }
    sem_close(&semaphore);
    return 0;
}
