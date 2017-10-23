#ifndef THREADS_H
#define THREADS_H

#include <stdio.h>
#include <pthread.h>
#include "memory.h"

#define SIZE 16         //max size of communication between the master and the slave
#define MAX_SIZE 512    //max size of each message between the master and the slave

void write_comm(char***, char*);
int read_comm(char***, char*);

pthread_t* create_thread(void*);

void *t_cli(void*);

void *t_server(void*);

void *t_client(void*);

void *t_cli_input(void*);
#endif