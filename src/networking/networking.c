#include "headers/networking.h"

void networking(char* param)
{
    if(strcmp(param, SERVER_MODE) == 0) create_thread(server);
    else create_thread(client);
    while(1);
}