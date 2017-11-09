#include "headers/http.h"

void build_http(char* content)
{
    char* buffer = malloc(strlen(content) + 1);
    strcpy(buffer, content);
    sprintf(content, "%s%s%s%s%s%d\r\n\r\n%s\n\r\n", BASE1, USR_AG, BASE2, TYPE, BASE3, strlen(buffer)+3, buffer);  //TODO: is content big enough?
    free(buffer);
}

char* get_http(char* str)
{
    str = strstr(str, "\r\n\r\n") + 4;      //The first \r\n\r\n is the end of our header
}