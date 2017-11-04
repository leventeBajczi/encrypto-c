#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>

#include "text/RSA/headers/rsa.h"           //rsa encryption interface
#include "text/headers/base64.h"            //base64 encoding interface
#include "networking/headers/networking.h"  //networking interface
#include "interfaces/headers/interfaces.h"  //cli interface
#include "misomosi/headers/memory.h"        //miso mosi memory allocation and operation


/* for CLI parameters and to specify their defaults - one-instruction startup is possible */ 
#define MODE_SWITCH         "-m"
#define CLIENT_SWITCH       "-c"
#define KEYS_SWITCH         "-k"
#define DIRECTORY_SWITCH    "-d"

#define DEFAULT_MODE        "client"
#define DEFAULT_CLIENT      "cli"
#define DEFAULT_KEYS        "./"
#define DEFAULT_DIRECTORY   "./messages"

#define CLI_CLIENT          "cli"


#define SIZE 16         //max size of communication between the master and the slave
#define MAX_SIZE 512    //max size of each message between the master and the slave

int start(char*, char*, char*, char*);
#endif