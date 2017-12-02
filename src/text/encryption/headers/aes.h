#ifndef AES_H
#define AES_H

#include <unistd.h>
#include <gcrypt.h>

void handle_aes_key(char* );
char* get_aes_key();
void encrypt_aes(char* );
void decrypt_aes(char* );


#endif