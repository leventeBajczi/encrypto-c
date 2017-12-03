#ifndef CLI_H
#define CLI_H

#include <stdio.h>
#include <stdlib.h>

#include "../../threads/headers/threads.h"
#include "../../misomosi/headers/misomosi.h"
#include "../../defines.h"

void* cli(void*);
void* listener(void*);

#endif