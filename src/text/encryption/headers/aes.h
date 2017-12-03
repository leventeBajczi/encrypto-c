#ifndef AES_H
#define AES_H

#include <unistd.h>
#include <gcrypt.h>
#include "../../headers/base64.h"
#include "rsa.h"
#include "randomdata.h"

#define MODE 1      //from /dev/urandom, the safest one

void handle_aes_key(char* );
char* get_aes_key();
void encrypt_aes(char** );
void decrypt_aes(char** );
void encrypt_private(char**, int);
void decrypt_private(char*, char*, int);
void generate_aes();


#endif