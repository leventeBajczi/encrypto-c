#include "headers/cli.h"

extern char** i_mosi;
extern char** i_miso;

void *cli(void* params){
    char* out = (char*)malloc(sizeof(char)*MAX_RESPONSE_SIZE);

    setbuf(stdout, NULL);
    create_thread(listener, NULL);

    while(1)
    {
        while(!read_comm(&i_mosi, &out))nanosleep((const struct timespec[]){{0, 10000000L}}, NULL);
        printf("\033[s\r\033[1A\r\033[K\r%s\033[u", out);
    }

    free(out);
}

void *listener(void* params)
{
    char* input = (char*)malloc(sizeof(char)*MAX_RESPONSE_SIZE);
    while(1)
    {
        int i = 0;
        while((input[i++] = fgetc(stdin)) != '\n' );
        write_comm(&i_miso, input);
    }
    free(input);
}