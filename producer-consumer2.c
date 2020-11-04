#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>
#include<math.h> 


#define BUFFER_SIZE 100

sem_t spaces;
sem_t items;
int counter =0; 
int buffer[BUFFER_SIZE];
int pindex = 0;
int cindex =0;
pthread_mutex_t mutex;
int seed = 252;



int produce(int id){
    int r = rand_r(&seed);
    printf("Producer %d produced %d ", id, r );
    return r;
}

void consume(int id, int value){
    printf("Consumer %d consumed %d", id, value);
}


void * producer (void *arg) {
    int * id = (int *) arg;
    for  (int i =0; i<10000; i++){
        int num = produce(*id);
        sem_wait(&spaces);
        pthread_mutex_lock ( &mutex);
        buffer[pindex] = num;
        pindex = (pindex +1 ) % BUFFER_SIZE;
        pthread_mutex_unlock (& mutex);
        sem_post(& items);
    }
    free(arg);
    return;
}

void * consumer (void * arg) {
    int * id = (int *) arg;
    for (int i =0; i<10000; i++){
        sem_wait(&items);
        pthread_mutex_lock(&mutex);
        int num = buffer[cindex];
        buffer[cindex] =-1;
        cindex = (cindex +1) % BUFFER_SIZE;
        pthread_mutex_unlock( &mutex);
        sem_post( &spaces);
        consume( *id, num);
    }
    free(id);
    return;
}

int main(int argc, char ** argv){

    sem_init(& spaces, 0, BUFFER_SIZE);
    sem_init(&items, 0, 0);

    pthread_mutex_init(&mutex, NULL);

    pthread_t threads [20];

    for ( int i=0 ;i<10 ; i++){
        int * id = malloc(sizeof(int));
        *id = i;
        pthread_create(&threads[i], NULL, producer, id);
    }

    for (int  j =10; j< 20; j++){
        int * id = malloc(sizeof(int));
        *id = j -10;
        pthread_create(&threads[j], NULL, producer, id);
    }
    for (int k =0; k<20; k++){
        pthread_join(threads[k], NULL);

    }    
    sem_destroy(&spaces);
    sem_destroy(&items);
    pthread_mutex_destroy(&mutex);
    return;
}