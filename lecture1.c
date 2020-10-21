#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
#include <errno.h>+
#define BUFFER_SIZE 1000
#define VALUE 2 * 25 +4

extern int errno;
char global_var = 'A';
char global_var2;

typedef struct point{
    double x;
    double y;
    double z;
} point_t;

typedef int pid_t; 

int bar(int v1, int v2);
int stack_push( point_t*s, void * value); // returns an error number if false
// void * is a point to an unknown type, i.e. it doesn't matter what the type is

// ./hello arg1 arg2    gives argc ==2 
int main (int argc, char** argv){
    // argc == number of arguments to the program 
    // (char*) * argv. array of strings 

    // for ./hello arg1 17 

    int count = atoi(argv[2]);

    return 0;

}
int function_name ( double arg1, int arg2, char arg3){
    int v = VALUE * 2; 
    //  == 2 * 25 +4 *2 != 108 !!!!!!!!
    int i; // stack allocated memory, dies at return 0;
    // even if u return i, i is stil deleted from the stack because the 
    // value is copied over to a new var
    global_var2 = 'B';
    for (int i =0; i< 10; i++){
        /* Comments in C */ 
    }

    point_t p1;
    p1.x = 1.9;
    p1.y = -2.5;
    p1.z = 0.3;
    
    return 0;
}
int init_header(struct point_t * h, int v1, double v2, struct point_t * v3){
    return 2;
}

// convention to change the first thing, i.e. header will be changed and initialized with all the other parameters
void add_to_point(point_t t1, point_t t2){

}

void string_stuff() {
    printf("Hello World:");
    char null_term = '\0';  // for strings this is the last char that needs to be added if manually creating a string
    char zero = '0';


    int z = -25 ;
    printf("the value of z is %d.\n", z);
    // u can have multiple formats and multiple parameters
    // fomat identifier is %d ?? you have to search through these 

    point_t p2; 
    p2.x = 1.5;
    p2.y = -3.3;
    p2.z = 9.1;
    printf("(%f, %f, %f) \n", p2.x, p2.y, p2.z);
}

// global memory: memory that is global to the program, constalty allocated and deleted at program termination
// heap memory: memory that is explicitly askde for and must be explictly returned, dramatically larger than stack space 
// stack memory: what is local to the function and its automatically throw away when the function returns, not infinite this is smaller 
void allocate_memory(){ 
    // allocates memeory to the heap for this 
    
    // malloc( /* how many bytes I actually need */);
    
    // integers only have a minimum size in C, they actually vary in size on different systems
    // malloc( sizeof (int));
    /* above is equal to the below usually */    
    // malloc (4);

    // allocates the memeory of the struct point 
    // malloc( sizeof ( point_t));

    // malloc returns the point to memory with no type 
    // this is garbage memory that is uninitialized 
    int * x = malloc(sizeof(int));
    int * y =x; // we only have to derefereence either x or y; 
    // initalize var by dereference the var
    *x = 0; 
    free ( x);
    point_t * p = malloc( sizeof (point_t));
    (*p).x = 99.9;
    (*p).y = 99;
    (*p).z = 98;

    //  OR 
    
    p->x = 99.9;
    p->y = 99;
    p->z = 98;

    //  to initilize everything to 0:
    free(p);
    memset(p,0 ,sizeof(point_t));
    free(p);   

    int stack_arr[10]; // contains garbage initially 
    int * heap_array = malloc(sizeof(int) *10 );
    stack_arr[2] =5; 
    heap_array[1] = 3;

    // there's no automatic array bounds checking 
   
    free( heap_array);

}

void initizalize_array(int * a, int capacity){
    for ( int i =0; i<capacity; i++){
        a[i] =0;
    }
    free(a);
    // OR 
    memset(a, 0, capacity * sizeof(int));
}

// int work (int x, int y){
//     return x + y;
// }

// int do_work() {
// //     int * a = malloc( sizeof(int ));
// //     *a =5;
// //     int *b = malloc (sizeof (int));
// //     *b = 7;
//     // int c = work(*a, * b);
//     int a = 5;
//     int b = 7;
//     int c = work(a,b);

//     // free (a);
//     // free(b);
//     return c;
// }



// int work (int *x, int *y){
//     return *x + *y;
// }

// int do_work() {
//     int a = 5;
//     int b = 7; // stack allocated 
//     int c = work( &a, & b); // creates a point to the stack allocated memory to a and b
//     return c;
// }

point_t add_points(point_t p1, point_t p2){
    point_t result;
    result.x = p1.x + p2.x;
    result.y = p1.y + p2.y;
    result.z = p1.z + p2.z;
}


// this throws an error b/c bar() function has not yet been defined
int foo(){
    return bar(7 ,11);
}

int bar(int v1, int v2){
    return v1 *v2;
}
// solution: we can create the header prototype before our actual code


int main() {
    char snum [5];

    printf("SDFSDFSDFD \n");
    int a = do_work();

    char buffer [33];
    snprintf(buffer, sizeof(buffer), "%d", a);    
    printf ("decimal: %s\n",buffer);

    return 0;
}