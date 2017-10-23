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
    //create_folder(directory);
    //check_keys(keyfiles);
    if(strcmp(client, CLI_CLIENT) == 0) create_thread(t_cli);
    if(strcmp(mode, SERVER_MODE) == 0)  create_thread(t_server);
    if(strcmp(mode, CLIENT_MODE) == 0)  create_thread(t_client);
    while(1);
    return 0;
}