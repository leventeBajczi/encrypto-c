#include "headers/interfaces.h"

void interfaces(char* param)
{
    if(strcmp(param, CLI_INTERFACE) == 0) create_thread(cli, NULL);
    else create_thread(cli, NULL);

    while(1);
}