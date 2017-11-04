#ifndef NETWORKING_H
#define NETWORKING_H

#include <string.h>

#include "client.h"
#include "server.h"
#include "../../threads/headers/threads.h"

#define CLIENT_MODE         "client"
#define SERVER_MODE         "server"

void networking(char*);

#endif