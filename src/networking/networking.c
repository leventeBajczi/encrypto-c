#include "headers/networking.h"

extern char** n_miso;
extern char** i_mosi;
extern char** n_mosi;
extern char** i_miso;

extern int running;

void networking(char* param)
{
    if(strcmp(param, SERVER_MODE) == 0){
        create_thread(server, NULL);
        create_thread(host_info, NULL);
    }
    else {
        char* private_key = NULL;
        char* public_key = NULL;
        int priv_len;
        int publ_len;
        generate_keypair(KEYLEN, &private_key, &priv_len, &public_key, &publ_len);
        write_pem("ENCRYPTED PRIVATE KEY", encode_base64(private_key, priv_len), "private.key");
        write_pem("NON-ENCRYPTED PUBLIC KEY", encode_base64(public_key, publ_len), "public.key");
        create_thread(client, NULL);

    }
    
    create_thread(router, NULL);
}

void* router(void* param)
{
    char* out = (char*)malloc(sizeof(char)*MAX_RESPONSE_SIZE);
    while(running)
    {
        if(read_comm(&n_miso, &out)) write_comm(&i_mosi, out);
        if(read_comm(&i_miso, &out)) {
            write_comm(&n_mosi, out);
        }
        nanosleep((const struct timespec[]){{0, 10000000L}}, NULL);
    }
    free(out);    
}