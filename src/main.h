#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>

#include "text/libtext.h"           //rsa encryption interface
#include "networking/headers/networking.h"  //networking interface
#include "interfaces/headers/interfaces.h"  //cli interface
#include "misomosi/headers/memory.h"        //miso mosi memory allocation and operation

#include "defines.h"
void sigint_handler();
int start(char*, char*);
#endif