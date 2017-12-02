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
#include "../../threads/headers/threads.h"
#include "../../text/headers/http.h"
#include "../../text/headers/json.h"
#include "../../text/encryption/headers/aes.h"
#include "../../text/encryption/headers/rsa.h"


#define PORTNUM 1111
#define MAX_ANSWER_SIZE 3584    //3.5kiB for the body
#define MAX_RESPONSE_SIZE 4096  //4kiB for the entire message
#define HEADER "HTTP/1.1 200 OK\nUser-agent: encrypto-0.1.0\nContent-Type: text/html\nContent-Length: "
#define KEYSIZE 512
#define AES_KEYLEN 32
#define CONNECTION_CONNECTED "Connected"

void handle_input(char*);
void handle_output(char*);
void* c_callback(void*);
void* client(void*);
void send_connected();
void send_key_request();
void send_aes_key(char* );
void send_public_key();
#endif