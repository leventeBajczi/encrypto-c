#include "main.h"



int main(int argc, char** argv){
    int i = 0;
    char* mode      = DEFAULT_MODE;
    char* client    = DEFAULT_CLIENT;
    char* directory = DEFAULT_DIRECTORY;
    char* keyfiles  = DEFAULT_KEYS;

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
        else{
            printf("Unrecognized CLI switch %s, quitting.", argv[i]);
            return -1;
        }
    }
    return start(mode, client, keyfiles, directory);
}

int start(char* mode, char* client, char* keyfiles, char* directory){
    pthread_t *main;
    //client mode
    if(strcmp(client, CLI_CLIENT) == 0) main = create_thread(t_cli);

    //role mode
    if(strcmp(mode, SERVER_MODE) == 0)  create_thread(t_server);
    else if(strcmp(mode, CLIENT_MODE) == 0)  create_thread(t_client);

    create_thread(t_listener);

    pthread_join(*main, NULL);
    return 0;
}