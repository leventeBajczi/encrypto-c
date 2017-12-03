#include "headers/rsa.h"


char* load_public_key()
{
    
}
void encrypt_rsa(char* key, char* content, int len)
{

}
void decrypt_rsa(char* content, int len)
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
    rsa_data = gcry_sexp_nth(rsa_keypair, 2);
    void* rsa_buf = calloc(1, KEYLEN*7);
    int i = 0, j = 0;
    len = 0;
    gcry_sexp_sprint(rsa_data, GCRYSEXP_FMT_CANON, rsa_buf, KEYLEN*7);
    while(j || !len)
    {
        switch(((char*)rsa_buf)[len])
        {
            case '(': len++; j++; break;
            case ')': 
                len++;
                j--; break;
            case ':': len+=i+1; i = 0; break;
            default: i=i*10 + ((char*)rsa_buf)[len]-'0'; len++; break;
        }
    }
    encrypt_private(&rsa_buf, len);
    char *priv = encode_base64(rsa_buf, len);
    free(rsa_buf);
    write_pem("PRIVATE KEY", priv, "private.key");  

    rsa_data = gcry_sexp_nth(rsa_keypair, 1);
    rsa_buf = calloc(1, KEYLEN*3);
    i = 0, j = 0;
    len = 0;
    gcry_sexp_sprint(rsa_data, GCRYSEXP_FMT_CANON, rsa_buf, KEYLEN*3);
    while(j || !len)
    {
        switch(((char*)rsa_buf)[len])
        {
            case '(': len++; j++; break;
            case ')': 
                len++;
                j--; break;
            case ':': len+=i+1; i = 0; break;
            default: i=i*10 + ((char*)rsa_buf)[len]-'0'; len++; break;
        }
    }

    priv = encode_base64(rsa_buf, len);
    free(rsa_buf);
    write_pem("PUBLIC KEY", priv, "public.key");  

    gcry_sexp_release(rsa_keypair);
    gcry_sexp_release(rsa_parms);
}
