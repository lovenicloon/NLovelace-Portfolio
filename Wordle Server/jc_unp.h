#include <sys/socket.h>     //socket functions
#include <arpa/inet.h>      //socket addr struct
#include <errno.h>          //for EINTR
#include <string.h>         //for bzero()
#include <stdio.h>          //printf(), read(), ...
#include <stdlib.h>         //exit()
#define SERV_PORT 15243     //server port
#define SA struct sockaddr  //socket addr
#define LISTENQ 1024        //bind()'s backlog
#define MAXLINE 4096
#define BUFFERSIZE 8192

