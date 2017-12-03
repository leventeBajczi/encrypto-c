#include "headers/aes.h"

gcry_cipher_hd_t aes_key;

void handle_aes_key(char* key)
{
    char* decoded = decode_base64(key);
    decrypt_rsa(decoded, strlen(key)*3/4);
    memcpy(aes_key, decoded,  strlen(key)*3/4);
}
char* get_aes_key()
{
    return encode_base64(&aes_key, sizeof(aes_key));
}
void encrypt_aes(char* content)
{
    int err = gcry_cipher_encrypt(aes_key, (unsigned char*) content, strlen(content), NULL, 0);
    if (err) {
        printf("gcrypt: could not encrypt with AES");
        abort();
    }
}
void decrypt_aes(char* content)
{
    int err = gcry_cipher_decrypt(aes_key, (unsigned char*) content, strlen(content), NULL, 0);
    if (err) {
        printf("gcrypt: could not decrypt with AES");
        abort();
    }
}

void encrypt_private(char** rsa, int len)
{
    gcry_cipher_hd_t aes_hd;
    char passwd_hash[32];
    char passwd[60];
    scanf("%s", passwd);
    size_t pass_len = passwd[0] ? strlen(passwd) : 0;

    if(!pass_len)
    {
        printf("Invalid password, quitting");
        abort();
    }

    int err = gcry_cipher_open(&aes_hd, GCRY_CIPHER_AES256, GCRY_CIPHER_MODE_CFB, 0);
    if (err) {
        printf("gcrypt: failed to create aes handle");
        abort();
    }

    gcry_md_hash_buffer(GCRY_MD_SHA256, (void*) &passwd_hash, (const void*) passwd, pass_len);

    err = gcry_cipher_setkey(aes_hd, (const void*) &passwd_hash, 32);
    if (err) {
        printf("gcrypt: could not set cipher key");
        abort();
    }

    err = gcry_cipher_setiv(aes_hd, (const void*) &passwd_hash, 16);
    if (err) {
        printf("gcrypt: could not set cipher initialization vector");
        abort();
    }

    err = gcry_cipher_encrypt(aes_hd, (unsigned char*) *rsa, len, NULL, 0);
    if (err) {
        printf("gcrypt: could not encrypt with AES");
        abort();
    }
    gcry_cipher_close(aes_hd);

}