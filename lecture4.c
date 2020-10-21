// void(*signal(int signo, void(*handler)(int))) ( int);

// // signo = signal number to watch for
// // handler = function to run when u get the signal =

// // to be passed to the above function
// void sig_handler (int signal_num){
//     // do something
// }


#include <stdio.h>
#include <stdlib.h> 
#include <signal.h>
#include <unistd.h>

volatile int quit =0;

void handler (int signo){
    quit =1;
}

int main(int argc, char** argv){
    // registers the signal handler

    sigset_t set;
    sigset_t previous;

    sigemptyset(& set);  // initializes the empty set
    sigaddset( &set, SIGINT); // add sigint to it

    sigprocmask(SIG_BLOCK, &set, &previous);
    // sigint is blocked in this section

    sigprocmask(SIG_SETMASK, &previous, NULL); // restore the previous mask
    // sigint is unvlocked again, if there is a pending request then it will be delivered 


    pause(); // makes program wait for a bit until its interrupted by a signal


    // signal(SIGINT, handler);

    // while (quit ==0)
    // {
    //     sleep(1);
    // }
    // printf("Time tp die \n");
    return 0;
}


