#include "headers/cli.h"

extern char** i_mosi;
extern char** i_miso;

void *cli(void* params){
    char* out = (char*)malloc(sizeof(char)*MAX_RESPONSE_SIZE);

    setbuf(stdout, NULL);
    create_thread(listener, NULL);

    while(1)
    {
        while(!read_comm(&i_mosi, out));
        printf("%s", out);
    }

    free(out);
}

void *listener(void* params)
{
    char* input = (char*)malloc(sizeof(char)*MAX_RESPONSE_SIZE);
    while(1)
    {
        scanf("%s", input);
        write_comm(&i_miso, input);
    }
    free(input);
}