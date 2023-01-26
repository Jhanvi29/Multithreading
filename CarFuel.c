#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>


int fuel = 0;
pthread_mutex_t mutexfuel;
pthread_cond_t condFuel;
void* fuel_filling(void* arg) {
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&mutexfuel);
        fuel += 60;
        printf("Filled fuel... %d\n", fuel);
        //pthread_cond_broadcast(&condFuel);
        pthread_mutex_unlock(&mutexfuel);
        pthread_cond_broadcast(&condFuel);
        sleep(1);

    }
    return 0;
}

void* car(void* arg) {


    pthread_mutex_lock(&mutexfuel);
    while (fuel < 40) {
        printf("No fuel. Waiting...\n");
        pthread_cond_wait(&condFuel , &mutexfuel);
    }
    fuel -= 40;
    printf("Got fuel. Now left: %d\n", fuel);
    pthread_mutex_unlock(&mutexfuel);
    return 0;

}

int main(int argc, char* argv[]) {
    pthread_t th[5];
    pthread_mutex_init(&mutexfuel , NULL);
    pthread_cond_init(&condFuel , NULL);

    for (int i = 0; i < 5; i++) {
        if (i == 1) {
            if (pthread_create(&th[i], NULL, &fuel_filling, NULL) != 0) {
                perror("Failed to create thread");
            }
        } else {
            if (pthread_create(&th[i], NULL, &car, NULL) != 0) {
                perror("Failed to create thread");
            }
        }
    }

    for (int i = 0; i < 5; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }

    pthread_mutex_destroy(&mutexfuel);
    pthread_cond_destroy(&condFuel);
    return 0;
}
