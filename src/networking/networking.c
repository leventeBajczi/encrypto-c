#include "headers/networking.h"

extern char** n_miso;
extern char** i_mosi;
extern char** n_mosi;
extern char** i_miso;

void networking(char* param)
{
    if(strcmp(param, SERVER_MODE) == 0) create_thread(server, NULL);
    else create_thread(client, NULL);
    
    create_thread(router, NULL);
}

void* router(void* param)
{
    char* out = (char*)malloc(sizeof(char)*MAX_RESPONSE_SIZE);
    while(1)
    {
        if(read_comm(&n_miso, out)) write_comm(&i_mosi, out);
        if(read_comm(&i_miso, out)) {
            write_comm(&n_mosi, out);
        }
    }
    free(out);    
}