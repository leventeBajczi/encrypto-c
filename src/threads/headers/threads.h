#ifndef THREADS_H
#define THREADS_H

#include <pthread.h>

#include "../../networking/headers/client.h"
#include "../../networking/headers/server.h"

#define MAX_THREADS 5   //Maximum number of threads this program is able to handle - no problem if bigger than actually needed

pthread_t* create_thread(void*);
#endif