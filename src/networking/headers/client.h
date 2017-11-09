#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h> 

#include "../../misomosi/headers/misomosi.h"

#include "../../text/headers/http.h"


#define PORTNUM 1111
#define MAX_ANSWER_SIZE 3584    //3.5kiB for the body
#define MAX_RESPONSE_SIZE 4096  //4kiB for the entire message

void handle_input(char*);
void handle_output(char*);
void* client(void*);
#endif