#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <math.h>

void* circle(void *args){
    int val = *(int*) args;
    printf("No of randon points to be generated %d \n" , val);
    int *totalPoint = malloc(sizeof(int));
    *totalPoint = 0;

    for(int i =0; i<val; i++){
        double X = (double)rand() / RAND_MAX;
        double Y = (double)rand() / RAND_MAX;

        if((X*X) + (Y*Y) <=1){
            //printf("Found points that form circle \n");
            *totalPoint = *totalPoint + 1;
        }
    }
    printf("Value in the circle subroutine %d \n" , *totalPoint);
    return (void*) totalPoint;

}

int main(int argc, char*argv[]){
    pthread_t th;
    srand(time(NULL));
    printf("Caluclating the value of pi \n");
    
    int *amtwanted = malloc(sizeof(int));
    *amtwanted = 10000;

    int *res = malloc(sizeof(int));

    
    if(pthread_create(&th , NULL, &circle, amtwanted) != 0){
        perror("Can not form the thread");
    }

    if(pthread_join(th, (void**) &res) !=0){
        perror("Can not join the threads");
    }

    printf("the value of total points in the main subroutine is %d \n" , *res);

    double points = 4.0 * (*res);
    double pi = points / (*amtwanted);

    printf("Approximate value of pi by Monte Carlo Mehtod is %f \n" , pi);

    return 0;



}
