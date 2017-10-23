#include "threads.h"

pthread_t handles[5];
short count = 0;

void create_thread(void* thread){
    pthread_create(&(handles[count++]), NULL, thread, NULL);
    
}

void *t_cli(void* params){
    printf("Hello from cli\n");
}

void *t_server(void* params){
    printf("Hello from server\n");
}

void *t_client(void* params){
    printf("Hello from client\n");
}