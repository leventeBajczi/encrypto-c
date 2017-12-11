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
#include "../../file/headers/io.h"

#include "../../text/libtext.h"

#include "../../defines.h"

void s_handle_input(char*);
void* server(void*);
void* callback(void*);
void* serverread(void*);
void* host_info(void*);

#endif