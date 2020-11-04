#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>
#include<math.h>
#include <sys/types.h>
#include <sys/stat.h>

#define B 20

sem_t spaces;
sem_t items;
int counter =0; 
int *buffer;

int produce(){

    ++counter;
    return counter;
}

void consume(int value){
    printf("consumed %d", value);
}


void * producer (void *arg) {
    int pindex = 0;
    while(counter < 10000){
        int v = produce();
        sem_wait( &spaces) ;
        buffer[pindex] = v;
        pindex = (pindex+1) % B;
        sem_post(&items);
    }
    return NULL;
}

void * consumer (void * ar) {
    int cindex=0; 
    int ctotal = 0;
    while( ctotal < 10000){
        sem_wait(&items);
        int temp = buffer[cindex];
        buffer[cindex] = -1;
        cindex = (cindex+1 ) % B;
        sem_post(&spaces);
        consume(temp);
        ++ctotal;
    }
    return NULL;   
}

int main(int argc, char ** argv){
    buffer= malloc(B * sizeof(int));
    for (int i =0; i< B; i++){
        buffer[i] =-1; // -1  reps empty space
    }

    sem_init(& spaces, 0, B);
    sem_init(&items, 0, 0);

    pthread_t prod;
    pthread_t con;

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&prod, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(con, NULL);

    free(buffer);
    
    sem_destroy(&spaces);
    sem_destroy(&items);

    return 0;
}