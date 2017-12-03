#include "headers/interfaces.h"

extern int running;

void interfaces(char* param)
{
    void* thread;
    if(strcmp(param, CLI_INTERFACE) == 0) thread = create_thread(cli, NULL);
    else thread = create_thread(gui, NULL);
    while(running)
    {
        nanosleep((const struct timespec[]){{0, 100000000L}}, NULL);
    }
}