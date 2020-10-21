#define _XOPEN_SOURCE 
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h> 
#include <string.h>
#include <unistd.h> 
#include <sys/wait.h> 


int main (int argc, char ** argv){
    int shmid = shmget( IPC_PRIVATE, 32, IPC_CREAT | 0666);

    int pid = fork();
    if (pid >0){ /* Parent */
        waitpid(pid, NULL , 0); // wait for child to run 
        void * mem = shmat(shmid, NULL, 0);
        printf("The nesage received from the child is %s \n", (char *) mem);
        shmdt(mem); // detach
        shmctl(shmid, IPC_RMID, NULL);  // schedule for deletion
    } else if (pid ==0){
        void * mem = shmat(shmid, NULL, 0);
        memset(mem, 0, 32);
        sprintf(mem, "hello world");
        shmdt(mem);
    }
    return 0; 
}