#include "main.h"

char** n_mosi;
char** n_miso;
char** i_mosi;
char** i_miso;
char** s_fifo;
char* serverip;
char* portnum;
char* connection;
char* partnerip;
char* name;
char* directory;
char* keyfiles;

int running = 1;

int main(int argc, char** argv){
    int i = 0;
    char* mode      = DEFAULT_MODE;
    char* client    = DEFAULT_CLIENT;
    directory       = DEFAULT_DIRECTORY;
    keyfiles        = DEFAULT_KEYS;
    serverip        = DEFAULT_SERVER;
    portnum         = DEFAULT_PORT;
    connection      = DEFAULT_CONNECTION;
    partnerip       = DEFAULT_PARTNERIP;
    name            = DEFAULT_NAME;

    signal(SIGINT, sigint_handler);

    for(i = 1; i<argc;i++){
        if      (strcmp(argv[i], MODE_SWITCH) == 0){
            mode = argv[++i];
        }
        else if (strcmp(argv[i], CLIENT_SWITCH) == 0){
            client = argv[++i];
        }
        else if (strcmp(argv[i], KEYS_SWITCH) == 0){
            keyfiles = argv[++i];
        }
        else if (strcmp(argv[i], DIRECTORY_SWITCH) == 0){
            directory = argv[++i];
        }
        else if (strcmp(argv[i], SERVER_SWITCH) == 0){
            serverip  = argv[++i];
        }
        else if (strcmp(argv[i], NAME_SWITCH) == 0){
            name      = argv[++i];
        }
        else if (strcmp(argv[i], PORT_SWITCH) == 0){
            portnum   = argv[++i];
        }
        else{
            printf("Unrecognized CLI switch %s, quitting.", argv[i]);
            return -1;
        }
    }
    return start(mode, client, keyfiles, directory);
}

int start(char* mode, char* client, char* keyfiles, char* directory){
    generate_keypair();

    allocate_str_array(&n_mosi, SIZE, MAX_SIZE);
    allocate_str_array(&n_miso, SIZE, MAX_SIZE);
    allocate_str_array(&i_mosi, SIZE, MAX_SIZE);
    allocate_str_array(&i_miso, SIZE, MAX_SIZE);
    allocate_str_array(&s_fifo, SIZE, MAX_SIZE);

    networking(mode);
    interfaces(client);
    
    free_str_array(&n_mosi, SIZE);
    free_str_array(&n_miso, SIZE);
    free_str_array(&i_mosi, SIZE);
    free_str_array(&i_miso, SIZE);
    free_str_array(&s_fifo, SIZE);
    return 0;
}


//SIGINT HANDLER
void sigint_handler()
{
    printf("Quitting program...");
    running = 0;
}