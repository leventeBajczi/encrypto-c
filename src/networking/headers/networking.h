#ifndef NETWORKING_H
#define NETWORKING_H

#include <string.h>

#include "client.h"
#include "server.h"
#include "../../threads/headers/threads.h"

#include "../../defines.h"

void networking(char*);
void* router(void*);

#endif