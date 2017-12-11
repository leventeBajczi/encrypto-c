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
#include "../../text/libtext.h"
#include "../../defines.h"

void handle_input(char*);
void handle_output(char*);
void* c_callback(void*);
void* client(void*);
void send_connected();
void send_key_request();
void send_aes_key(char* );
void send_public_key();
#endif