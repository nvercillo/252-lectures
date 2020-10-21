#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h> // file control
#include <unistd.h>

typedef struct sfsdfsdf{

} FILE;

void readfile(int fd);

int main (int argc, char ** argv){


    FILE * fp;
    int i , isquared;

    fp = fopen("res.data", "r");
    if ( fp == NULL){
        return -1;
    }


    while (fscanf(fp, "%d,%d\n", &i, &isquared) == 2){

        // fscanf returns the number of variables that i request
        // here we're asking for 2, if we get less then two throw error
        printf("i: %d, isquared: %d\n", i, isquared);
    }
    // if ( argc != 2){
    //     printf("Usage: %s <filename> \n", argv[0]);
    //     return -1;   
    // }
    // int fd = open (argv[1], O_RDONLY);
    // if (fd == -1){   // open failed
    //     pritnf("Unable to open file ! %s is invalid name?\n" , argv[1]);
    //     return -1;
    // }

    // readfile(fd);
    // close(fd);
    // return 0; 
}


void readfile(int fd){
    int buf_size = 256; 
    char * buffer = malloc(buf_size);
    while (1)
    {
        memset(buffer, 0 , buf_size);
        int bytes_read = read(fd, buffer, buf_size-1);
        if (bytes_read == 0){
            break;
        }
        printf ("%s", buffer);
    }
    printf("\nEnd of File.\n");
    free(buffer);
}


 

// void write_points_to_file ( point * p  FILE f ) {
//     while( p != NULL){
//         fprintf(f, "(%d, %d, %d) \n", p->x, p->y, p->z);
//         p = p->next;
//     }
// }


// // buffer is destination where the data is going to be read to and count is how many bits of data should we read at most
// // the number we ask for may be too big for the amount of bytes in the file
// ssize_t read (int file_descriptor, void * buffer, size_t count);


// int main ()
// {
//   int i;
//   char buffer [33];
//   printf ("Enter a number: ");
//   scanf ("%d",&i);
//   snprintf(buffer, sizeof(buffer), "%d", i);
//   printf ("decimal: %s\n",buffer);
// //   int bytesRead = read(file, buffer, numBytes;
//   return 0;
// }


