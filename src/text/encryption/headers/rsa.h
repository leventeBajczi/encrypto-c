#ifndef RSA_H
#define RSA_H

#include <unistd.h>
#include <gcrypt.h>
#include "../../../file/headers/io.h"
#include "../../headers/base64.h"
#define KEYLEN 256

char* load_public_key();
void encrypt_rsa(char*, char*);
void decrypt_rsa(char*);
void generate_keypair();

#endif