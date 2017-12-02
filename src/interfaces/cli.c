#include "headers/cli.h"

extern char** i_mosi;
extern char** i_miso;

extern int running;

void *cli(void* params){
    char* out = (char*)malloc(sizeof(char)*MAX_RESPONSE_SIZE);

    setbuf(stdout, NULL);
    create_thread(listener, NULL);

    while(running)
    {
        while(running && !read_comm(&i_mosi, &out))nanosleep((const struct timespec[]){{0, 10000000L}}, NULL);
        if(running)printf("\033[s\r\033[1A\r\033[K\r%s\033[u\n", out);
    }

    free(out);
}

void *listener(void* params)
{
    char* input = (char*)malloc(sizeof(char)*MAX_RESPONSE_SIZE);
    while(running)
    {
        int i = 0;
        while(running && (input[i++] = fgetc(stdin)) != '\n' );
        input[i] = 0;
        if(running)write_comm(&i_miso, input);
    }
    free(input);
}