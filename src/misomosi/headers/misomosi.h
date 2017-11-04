#ifndef MISOMOSI_H
#define MISOMOSI_H

#define SIZE 16         //max size of communication between the master and the slave
#define MAX_SIZE 512    //max size of each message between the master and the slave


#include <string.h>
#include <stdlib.h>
#include "memory.h"

void write_comm(char***, char*);
int read_comm(char***, char*);


#endif