#ifndef RSA_H
#define RSA_H

char* load_public_key();
void encrypt_rsa(char*, char*);
void decrypt_rsa(char*);
void generate_keypair();

#endif