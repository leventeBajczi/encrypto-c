#include "headers/interfaces.h"

void interfaces(char* param)
{
    if(strcmp(param, CLI_INTERFACE) == 0) pthread_join(*create_thread(cli, NULL), NULL);
    else pthread_join(*create_thread(gui, NULL), NULL);
}