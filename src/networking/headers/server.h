#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "../../misomosi/headers/misomosi.h"
#include "../../threads/headers/threads.h"

#include "../../text/headers/http.h"

#define PORTNUM 1111
#define MAX_ANSWER_SIZE 3584    //3.5kiB for the body
#define MAX_RESPONSE_SIZE 4096  //4kiB for the entire message
#define HEADER "HTTP/1.1 200 OK\nUser-agent: encrypto-0.1.0\nContent-Type: text/html\nContent-Length: "
#define CONCURR_CLIENTS 5

void s_handle_input(char*);
void* server(void*);
void* callback(void*);
void* serverread(void*);
#endif