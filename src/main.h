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
#define SERVER_SWITCH       "-s"
#define NAME_SWITCH         "-n"
#define PORT_SWITCH         "-p"

#define DEFAULT_MODE        "client"
#define DEFAULT_CLIENT      "cli"
#define DEFAULT_KEYS        "./"
#define DEFAULT_DIRECTORY   "./messages"
#define DEFAULT_SERVER      "127.0.0.1"
#define DEFAULT_NAME        "Anon"
#define DEFAULT_PORT        "0"
#define DEFAULT_CONNECTION  "Not connected"
#define DEFAULT_PARTNERIP   "-"

#define SIZE 16         //max size of communication between the master and the slave
#define MAX_SIZE 4096   //max size of each message between the master and the slave

void sigint_handler();
int start(char*, char*, char*, char*);
#endif