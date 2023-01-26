#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <math.h>

int list1[5] = {7, 12, 19, 3, 18};
int list2[5] = {4, 2, 6, 15, 8};
int list3[10];
void *sort1(void* args){

    printf("Sorting list 1 \n");
    sleep(1);
    for(int i=0; i<4; i++){
        for(int j=0; j<5-i-1; j++){
            if(list1[j] > list1[j+1]){
                int temp = list1[j+1];
                list1[j+1] = list1[j];
                list1[j] = temp;

            }
        }
    }

    return 0;
}

void *sort2(void* args){
    printf("sorting list 2 \n");
    sleep(2);
    for(int i=0; i<4; i++){
        for(int j=0; j<5-i-1; j++){
            if(list2[j] > list2[j+1]){
                int temp = list2[j+1];
                list2[j+1] = list2[j];
                list2[j] = temp;

            }
        }
    }


    return 0;

}

void *merge(void *args){
    sleep(3);
    for(int i=0; i<5; i++){
        list3[i] = list1[i];
    }  

    for(int i=0; i<5; i++){
        //printf("%d " , list2[i]);
        list3[i+5] = list2[i];
    } 
    for(int i=0; i<9; i++){
        for(int j=0; j<10-i-1; j++){
            if(list3[j] > list3[j+1]){
                int temp = list3[j+1];
                list3[j+1] = list3[j];
                list3[j] = temp;

            }
        }
    }
    
    return 0;
}

int main(int args, char* argv[]){

    pthread_t th[3];
    for(int i=0; i<3; i++){
        if(i==0){
            if(pthread_create(&th[0] , NULL , &sort1 , NULL) !=0){
                perror("Thread not created");
            }
        }
        else if(i==2){
            if(pthread_create(&th[1] , NULL , &sort2, NULL) != 0){
                perror("Thread not created");
            }
        }
        else{
            if(pthread_create(&th[2] , NULL , &merge, NULL) !=0){
                perror("Thread not created");
            }
        }
    }

    for(int i=0; i<3; i++){
        if(pthread_join(th[i] , NULL) !=0){
            perror("Thread not joined");
        }

    }

    for(int i=0 ; i<10; i++){
        printf("%d " , list3[i]);
        
    }


    return 0;
}
