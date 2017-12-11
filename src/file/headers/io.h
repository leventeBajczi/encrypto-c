#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <stdlib.h>
#include "../../text/libtext.h"
#include "../../defines.h"


void log_file(char* , char* , char*);
char* read_key(char*);
char* load_log();
void write_pem(const char* , char* , const char*);

#endif