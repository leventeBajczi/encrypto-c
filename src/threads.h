#ifndef THREADS_H
#define THREADS_H

#include <stdio.h>
#include <pthread.h>

void create_thread(void*);

void *t_cli(void*);

void *t_server(void*);

void *t_client(void*);
#endif