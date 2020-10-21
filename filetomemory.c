#define _XOPEN_SOURCE 
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h> 
#include <string.h>
#include <unistd.h> 
#include <sys/wait.h> 
#include <sys/stat.h> 
#include <fcntl.h>
#include <sys/mman.h>


int main (int argc, char ** argv){
    int fd = open("example.txt", O_RDWR);

    struct stat st; 
    stat("example.txt", &st);

    ssize_t size = st.st_size;

    void *mapped = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);


    int pid = fork();
    if (pid >0){ /* Parent */
        waitpid(pid, NULL , 0); // wait for child to run 
        printf("the new content of the file is %s, \n", (char *) mapped);
        munmap( mapped, size);
    } else if (pid ==0){
        memset(mapped, 0, size);
        sprintf(mapped, "it is now overwritten");

        msync( mapped, size , MS_SYNC);
        munmap(mapped, size);

    }
    return 0; 
}