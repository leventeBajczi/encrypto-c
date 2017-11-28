#include "headers/interfaces.h"

void interfaces(char* param)
{
    if(strcmp(param, CLI_INTERFACE) == 0) create_thread(cli, NULL);
    else create_thread(gui, NULL);

    while(1)nanosleep((const struct timespec[]){{0, 10000000L}}, NULL);;
}