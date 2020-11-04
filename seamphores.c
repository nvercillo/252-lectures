
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <getopt.h>
#include <pthread.h>
#include <stdbool.h>
#include <semaphore.h>

typedef struct{
    void * element;

} single_link_t;

bool push_front(single_link_t * list, void * obj){
    single_link_t * tmp = malloc(sizeof(single_link_t));

    if (tmp == NULL) return false;

    tmp->element = obj;

    sem_wait( & (list->sem));{
    tmp->next = list->head;
    list->head = tmp;
    

    if ( list->size == 0){
        list->tail = tmp;
    }
    ++ (list->size);
    } sem_post(&(list->sem));
    return true;
} 

int main(){
    return 0;
}