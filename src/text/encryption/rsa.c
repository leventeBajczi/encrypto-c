#include "headers/rsa.h"


char* load_public_key()
{

}
void encrypt_rsa(char* key, char* content)
{

}
void decrypt_rsa(char* content)
{

}
void generate_keypair()
{
    gcry_error_t err = 0;
    gcry_sexp_t rsa_parms;
    gcry_sexp_t rsa_keypair;
    gcry_sexp_t rsa_data; 

    printf("Generating a new keypair, please hold still....\n");
    
    err = gcry_sexp_build(&rsa_parms, NULL, "(genkey (rsa (nbits 4:2048)))");
    if (err) {
        printf("gcrypt: failed to create rsa params");
        abort();
    }

    err = gcry_pk_genkey(&rsa_keypair, rsa_parms);
    if (err) {
        printf("gcrypt: failed to create rsa key pair");
        abort();
    }

    printf("Key successfully generated, please provide pass to lock private files:\n");
    
    int len;
    rsa_data = gcry_sexp_nth(rsa_keypair, 1);
    rsa_data = gcry_sexp_nth(rsa_data, 1);
    void* rsa_buf = calloc(1, KEYLEN*3);
    int i = 0;
    len = 0;
    gcry_sexp_sprint(rsa_data, GCRYSEXP_FMT_CANON, rsa_buf, KEYLEN*3);
    while(i || !len)
    {
        if(((char*)rsa_buf)[len] == '(')i++;
        else if(((char*)rsa_buf)[len] == ')')i--;
        len++;
    }

    char *priv = encode_base64(rsa_buf, len);
    write_pem("PRIVATE KEY", priv, "private.key");

    if(rsa_data = gcry_sexp_find_token(rsa_keypair,"public-key",0))
    {
        //write_pem("PUBLIC KEY", encode_base64((uint8_t*)rsa_data,strlen((char*)rsa_data)), "public.key");
    }
    

}