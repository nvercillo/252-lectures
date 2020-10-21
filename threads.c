#include <stdlib.h> 
#include <stdio.h> 
#include <pthread.h>

void * run (void * arg){
    char *a  = (char *) arg;
    printf("Provided argument is %s \n", a);
    int * res = malloc(sizeof(int));
    *res = 69;
    return res;
}

int main(int argc, char** argv){
    if (argc != 2){
        printf("Invalid args. \n");
        return -1;
    }

    pthread_t t; 

    void * vr;
    pthread_create(&t, NULL, run, argv[1]);
    pthread_join(t, &vr);
    int *r = (int *) vr;

    printf("the other thread returned  %d \n", *r);

    free(vr);
    return;
}