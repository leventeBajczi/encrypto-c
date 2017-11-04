#include "main.h"

char** n_mosi;
char** n_miso;
char** i_mosi;
char** i_miso;

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
    allocate_str_array(&n_mosi, SIZE, MAX_SIZE);
    allocate_str_array(&n_miso, SIZE, MAX_SIZE);
    allocate_str_array(&i_mosi, SIZE, MAX_SIZE);
    allocate_str_array(&i_miso, SIZE, MAX_SIZE);

    networking(mode);
    interfaces(client);
    
    free_str_array(&n_mosi, SIZE);
    free_str_array(&n_miso, SIZE);
    free_str_array(&i_mosi, SIZE);
    free_str_array(&i_miso, SIZE);
    return 0;
}