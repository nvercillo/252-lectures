

// int socket(int domain, int type, int protocol);
// // domain-> address format: AF_INET (PIv4)
// // type what kind of data: SOCK_DGRAM or SOCK_STREAN data gran ir connection stream 
// // protocol: how data is trsnsported: ) for default TCP/IP


// struct sockaddr_in{
//     sa_family_t sin_family; /* Address Family*/
//     in_port_t sin_port;  /* Port Number*/
//     struct in_addr sin_addr;  /* IPv4 Address */
// }

// struct sockadd_in addr;
// add.sin_famil = AF_INET
// sinport = htons(2520) like ECE 252 
// s.addr = htonl (INADD_ANY) -> chooses the address of the current computer 


// int main(){
//     struct addrinfo hints;
//     struct addrinfo *serverinfo;

//     memset(&hints, 0, sizeof(hints)); // make sure the srtuct is empty
//     hints.ai_famility = AF_INET; // choose PIv4
//     hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
//     hints.ai_flags = AI_PASSIVE;  // fill in IP for me


//     int res = getaddrinfo("www.stefan/com ", "2520", &hints, &serverinfo);
    
//     struct sockaddr_in * sain = (struct sockadd_in *) serverinfo->ai_addr;

//     freeaddrinfo(serverinfo);
// }






// int socket(int domain, int type, int protocol);
// // domain-> address format: AF_INET (PIv4)
// // type what kind of data: SOCK_DGRAM or SOCK_STREAN data gran ir connection stream 
// // protocol: how data is trsnsported: ) for default TCP/IP


// struct sockaddr_in{
//     sa_family_t sin_family; /* Address Family*/
//     in_port_t sin_port;  /* Port Number*/
//     struct in_addr sin_addr;  /* IPv4 Address */
// }

// struct sockadd_in addr;
// add.sin_famil = AF_INET
// sinport = htons(2520) like ECE 252 
// s.addr = htonl (INADD_ANY) -> chooses the address of the current computer 


// int main(){
//     struct addrinfo hints;
//     struct addrinfo *serverinfo;

//     memset(&hints, 0, sizeof(hints)); // make sure the srtuct is empty
//     hints.ai_famility = AF_INET; // choose PIv4
//     hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
//     hints.ai_flags = AI_PASSIVE;  // fill in IP for me


//     int res = getaddrinfo("www.stefan/com ", "2520", &hints, &serverinfo);
    
//     struct sockaddr_in * sain = (struct sockadd_in *) serverinfo->ai_addr;

//     freeaddrinfo(serverinfo);
// }




#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h> 
#include <unistd.h> 
#include <string.h>
#include <netdb.h>


int main (int argc, char ** argv){
    
    int pid = fork();

    if (pid < 0){
        printf("Fork failed");
        return -1;
    } else if (pid ==0){   // child process sends the message and terminates

        printf("The child process will take a nap to give the server time to set up \n");
        sleep(4);
        
        struct addrinfo hints;
        struct addrinfo *serverinfo;
        memset(&hints, 0, sizeof hints);

        hints.ai_family = AF_INET;
        hints.ai_socktype =  SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE;

        // address referrs to our own computer
        int result = getaddrinfo( "127.0.0.1", "2520", &hints, &serverinfo);
        // check result here ....
        
        struct sockaddr_in * sain = (struct sockaddr_in*) serverinfo->ai_addr; // takes the first result (in case there are multiple)
        
        int clientsock = socket (serverinfo->ai_family, serverinfo->ai_socktype, serverinfo->ai_protocol);
        
        
        int c = connect( clientsock, serverinfo->ai_addr, serverinfo->ai_addrlen);
        if(c == -1){
            printf("Could not connect.\n");
            return -1;
        }


        char *message = malloc(20);
        memset(message, 0, 20);
        sprintf(message, "Messsage %d." , 1138); // addds 1138 to messsage
        send(clientsock, message, strlen(message) +1, 0); // null terminator not counted in the length of the string which is why there is + 1
        close(clientsock);
        free(message);
    } else {
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(2520);
        addr.sin_addr.s_addr = htonl( INADDR_ANY);

        int socketfd = socket(AF_INET, SOCK_STREAM, 0);
        
        bind (socketfd, (struct sockaddr*) &addr, sizeof(addr));
        listen(socketfd, 10);

        int newsocketfd;

        char* received = malloc(20);
        newsocketfd = accept(socketfd, NULL, NULL);
        memset(received, 0, 20);

        recv(newsocketfd, received, 20, 0);
        printf("Server recieved %s\n", received);
        close(newsocketfd);
        free(received);
        close (socketfd);
    }
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
