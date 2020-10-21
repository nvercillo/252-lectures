#include <stdio.h>
#include <stdlib.h> 
#include <signal.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h> 


struct msg{
    long mtype;
    int data;

};

int main(int argc, char** argv ){
    int msgqid = msgget(IPC_PRIVATE, 0666 | IPC_CREAT);

    int pid = fork();

    if (pid > 0){
        // this is the parent process
        struct msg m;
        m.mtype  = 42;
        m.data = 252;
        // the 0 makes us just wait so this would be blocking a send, IPC_NOWAIT  can also be used 
        msgsnd( msgqid, &m, sizeof(struct msg), 0); 
    } else if ( pid == 0){
        // child
        struct msg m2;
        // recieve message of type 421
        // we cant do anything till we get this 
        msgrcv (msgqid, &m2, sizeof(struct msg), 42, 0); // 0 blocks this?  
        printf("Received %d! \n", m2.data);
        msgctl(msgqid, IPC_RMID, NULL); // destroys the message queue 
    }
    return 0;
}


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>

#define CITIES_LENGTH 7
#define NUM_CITIES (CITIES_LENGTH - 1)

static const char* cities[] = { "Central City", "Starling City", "Gotham City", "Metropolis", "Coast City", "National City" };

const int distances[CITIES_LENGTH - 1][ CITIES_LENGTH - 1] = {
    {0, 793, 802, 254, 616, 918},
    {793, 0, 197, 313, 802, 500},
    {802, 197, 0, 496, 227, 198},
    {254, 313, 496, 0, 121, 110},
    {616, 802, 227, 121, 0, 127},
    {918, 500, 198, 110, 127, 0}
};

int initial_vector[CITIES_LENGTH] = { 0, 1, 2, 3, 4, 5, 0 };

typedef struct {
    int cities[CITIES_LENGTH];
    int total_dist; 
} route;

void print_route ( route* r ) {
    printf ("Route: ");
    for ( int i = 0; i < CITIES_LENGTH; i++ ) {
        if ( i == CITIES_LENGTH - 1 ) {
            printf( "%s\n", cities[r->cities[i]] );
        } else {
            printf( "%s - ", cities[r->cities[i]] );
        }
    }
}

void calculate_distance( route* r ) {
    if ( r->cities[0] != 0 ) {
        printf( "Route must start with %s (but was %s)!\n", cities[0], cities[r->cities[0]]);
        exit( -1 );
    } 
    if ( r->cities[6] != 0 ) {
        printf( "Route must end with %s (but was %s)!\n", cities[0], cities[r->cities[6]]);
        exit ( -2 );
    }
    int distance = 0;
    for ( int i = 1; i < CITIES_LENGTH; i++ ) {
        int to_add = distances[r->cities[i-1]][r->cities[i]];
        if ( to_add == 0 ) {
            printf( "Route cannot have a zero distance segment.\n");
            exit ( -3 );
        }
        distance += to_add;
    }
    r->total_dist = distance;
}

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void permute(route* r, int left, int right, route* best, int * routeNum ) {
    if (left == right) {
        *routeNum += *routeNum;
        // print_route(*routeNum);
        // calculate_distance(r);
        // if (r->total_dist < best->total_dist) {
        //     memcpy(best, r, sizeof(route));
        // }

        return;
    }

    for (int i = left; i <= right; i++) {
        swap(&r->cities[left], &r->cities[i]);
        permute(r, left + 1, right, best, routeNum);
        swap(&r->cities[left], &r->cities[i]);
    }
}   

route* find_best_route( ) {
    route* candidate = malloc( sizeof(route) );

    memcpy (candidate->cities, initial_vector, CITIES_LENGTH * sizeof( int ));
    candidate->total_dist = 0;

    route* best = malloc( sizeof(route) );
    memset( best, 0, sizeof(route) );
    best->total_dist = 999999;
    
    // route number 
    int * r = malloc(sizeof(int));
    *r = 0;    
    free(r);

    permute( candidate, 1, 5, best, r);

    free( candidate );
    return best;
}

int factorial(int num){
    int res;
    res =1;
    while (num >1){
        res *= num;
        num --;
    }
    return res;
}

int main( int argc, char** argv ) {
    route * best = find_best_route( );
    // route * permutations = malloc( sizeof(route) * )
    print_route( best );
    printf( "Distance: %d\n", best->total_dist ); 
    int numPermutations = factorial( CITIES_LENGTH -2);
    printf("counter %d\n", numPermutations);
    
    route * routePermutes = malloc( sizeof(route) * numPermutations);
    int * rnum = malloc(sizeof(int));


    // int * arr = malloc(sizeof(int) *5 );
    // int * heap_array = malloc(sizeof(int) *10 );
    // memset(heap_array, 0, sizeof(int) * 10);

    // // for (int i =0; i< sizeofheap_array)/sizeof(int);  i++){
    // for (int i =0; i< 10; i++){
    //     printf("%d\n", heap_array[i]);
    // }

    // arr[0]->
    free( best);
    return 0;
}

