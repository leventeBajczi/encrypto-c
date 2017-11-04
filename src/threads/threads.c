#include "headers/threads.h"

pthread_t handles[MAX_THREADS];
short count = 0;

pthread_t* create_thread(void* thread){
    pthread_create(&(handles[count]), NULL, thread, NULL);
    return &(handles[count++]);
}