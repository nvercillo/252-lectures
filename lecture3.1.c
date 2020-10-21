#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/wait.h>

int main ()
{
  pid_t pid;
  int child_status; 
  pid = fork(); // we now have two completely copied processes


  if ( pid < 0){
    printf("Error");
  } else if (pid == 0){

    // will show up first or second
    printf("child executing");
  } else {
    // will show up first or second
    printf("parent executing");
    waitpid(pid, &child_status, 0);

    // this will always run last because we're waiting for the child to execute
    printf("This parent process. The child process returned %d",  child_status);
  }
  return 0; 
}

