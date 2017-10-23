#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include "threads.h"

#define MODE_SWITCH         "-m"
#define CLIENT_SWITCH       "-c"
#define KEYS_SWITCH         "-k"
#define DIRECTORY_SWITCH    "-d"

#define DEFAULT_MODE        "client"
#define DEFAULT_CLIENT      "cli"
#define DEFAULT_KEYS        "./"
#define DEFAULT_DIRECTORY   "./messages"

#define CLIENT_MODE         "client"
#define SERVER_MODE         "server"

#define CLI_CLIENT          "cli"

int start(char*, char*, char*, char*);

#endif