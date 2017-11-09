#ifndef HTTP_H
#define HTTP_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void build_http(char*);
char* get_http(char*);

#define BASE1       "HTTP/1.1 200 OK\nUser-agent: "
#define USR_AG      "encrypto-0.1.0"
#define BASE2       "\nContent-Type: "
#define TYPE        "text/html"
#define BASE3       "Content-Length: "

#endif