#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/wait.h>

int executeA();
int executeB();

int main (int argc, char** argv)
{
    int  childRes, parentRes;
    pid_t pid = fork();
    if  (pid< 0){
        return -1;
    } else if ( pid ==0){
        childRes = executeB();
        return childRes;
    } else{
        parentRes = executeA();
        wait(&childRes);
    }

    if (childRes == 0 && parentRes == 0){
        printf("complete");
        return 0;
    }


    if (childRes != 2){
        printf ("error occured in child thread %d", childRes);
    }
    if (parentRes != 1 ){
        printf (("error occured in the paretn thread"));
    }
    
    return -1;
}
 
int executeA(){
    return 1 ;
}
int executeB(){
    return 2;
}