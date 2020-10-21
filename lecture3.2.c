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
    return 1;
  } else if (pid == 0){

    // will show up first or second
    execlp("/bin/ls", "ls", NULL);

    // this will never run, because the memory and PC is reset by exec call
    printf("child executing");

  } else {
    // will show up first or second
    printf("parent executing");
    wait(&child_status);

    // this will always run last because we're waiting for the child to execute
    printf("This parent process. The child process returned %d",  child_status);
  }
  return 0; 
}
 

// 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>

#define CITIES_LENGTH 7
#define NUM_CITIES (CITIES_LENGTH - 1)
#define PARENTP 99999

int factorial(int num);

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

typedef struct message{
    long mtype;
    int data;

} msg;

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

void permute(route* r, int left, int right,  int * routeNum, route * routePerms){
    if (left == right) {
        routePerms[*routeNum] = *r;
        *routeNum += 1;
        return;
    }
    
    for (int i = left; i <= right; i++) {
        swap(&r->cities[left], &r->cities[i]);
        permute(r, left + 1, right, routeNum, routePerms);
        swap(&r->cities[left], &r->cities[i]);
    }
}   

route* find_best_route() {
    route* candidate = malloc( sizeof(route) );

    memcpy (candidate->cities, initial_vector, CITIES_LENGTH * sizeof( int ));
    candidate->total_dist = 0;

    route* best = malloc( sizeof(route) );
    memset( best, 0, sizeof(route) );
    best->total_dist = PARENTP;
    
    // route iteration number 
    int * rn = malloc(sizeof(int));
    *rn = 0;

    int numPermutations = factorial( CITIES_LENGTH -2);
    // printf("counter %d\n", numPerutations);
    route * routePermutes = malloc( sizeof(route) * numPermutations);

    permute( candidate, 1, 5, rn, routePermutes);

    int pid = fork();
    for (int i=0; i<numPermutations; i++){
        // get child process
        if (pid > 0){
            return best;
        } else {
            int pid1 = fork();
            route * r = &routePermutes[i];

            // print_route(*routeNum);
            calculate_distance(r);
            if (r->total_dist < best->total_dist){
                memcpy(best, r, sizeof(route));
            }   
        }
    }

    printf("num: %d\n", best->total_dist);
    free(routePermutes);
    free(rn);
    free(candidate);
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
    if (best->total_dist != PARENTP){
        print_route( best );
        printf( "Distance: %d\n", best->total_dist ); 
    }
    
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




#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>

#define CITIES_LENGTH 7
#define NUM_CITIES (CITIES_LENGTH - 1)
#define PARENTP 99999

int factorial(int num);

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

typedef struct message{
    long mtype;
    int data;

} msg;

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

void permute(route* r, int left, int right,  int * routeNum, route * routePerms){
    if (left == right) {
        routePerms[*routeNum] = *r;
        *routeNum += 1;
        return;
    }
    
    for (int i = left; i <= right; i++) {
        swap(&r->cities[left], &r->cities[i]);
        permute(r, left + 1, right, routeNum, routePerms);
        swap(&r->cities[left], &r->cities[i]);
    }
}   

route* find_best_route() {
    route* candidate = malloc( sizeof(route) );

    memcpy (candidate->cities, initial_vector, CITIES_LENGTH * sizeof( int ));
    candidate->total_dist = 0;

    route* best = malloc( sizeof(route) );
    memset( best, 0, sizeof(route) );
    best->total_dist = PARENTP;
    
    // route iteration number 
    int * rn = malloc(sizeof(int));
    *rn = 0;

    int numPermutations = factorial( CITIES_LENGTH -2);
    // printf("counter %d\n", numPerutations);
    route * routePermutes = malloc( sizeof(route) * numPermutations);

    permute( candidate, 1, 5, rn, routePermutes);

    int pid = fork();
    for (int i=0; i<numPermutations; i++){
        // get child process
        if (pid > 0){
            return best;
        } else {
            int pid1 = fork();
            route * r = &routePermutes[i];

            // print_route(*routeNum);
            calculate_distance(r);
            if (r->total_dist < best->total_dist){
                memcpy(best, r, sizeof(route));
            }   
        }
    }

    printf("num: %d\n", best->total_dist);
    free(routePermutes);
    free(rn);
    free(candidate);
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
    if (best->total_dist != PARENTP){
        print_route( best );
        printf( "Distance: %d\n", best->total_dist ); 
    }
    
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


void run_server( ) {
  struct sockaddr_in client_addr;
  int client_addr_size = sizeof( struct sockaddr_in );
  char* msg = "Hello World";

  int socketfd = socket( AF_INET, SOCK_STREAM, 0 );
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons( 2520 );
  server_addr.sin_addr.s_addr = htonl( INADDR_ANY );

  while( !quit ) { /* Can be changed elsewhere in the program */

    bind( socketfd, (struct sockaddr*) &server_addr, sizeof( server_addr ));
    listen( socketfd, 5 );
    accept( socketfd, (struct sockaddr*) &client_addr, &client_addr_size );

    send( sockfd, msg, strlen(msg), 0 );

  }

  close( socketfd );
}

 
