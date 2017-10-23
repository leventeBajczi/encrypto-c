#include "threads.h"

char** mosi; 
char** miso;

pthread_t handles[5];
short count = 0;

pthread_t* create_thread(void* thread){
    pthread_create(&(handles[count]), NULL, thread, NULL);
    return &(handles[count++]);
}

void *t_cli(void* params){
    allocate_str_array(&mosi, SIZE, MAX_SIZE);
    allocate_str_array(&miso, SIZE, MAX_SIZE);
    create_thread(t_cli_input); //Catch any inputs
    char* out = (char*)malloc(sizeof(char)*MAX_SIZE);
    while(1){
        if(read_comm(&miso, out)){
            printf("\n%s\n\n", out);
        }
    }
}


void *t_cli_input(void* params){
    
    char* input = (char*)malloc(sizeof(char)*MAX_SIZE);
    while(1){
        scanf("%s", input);
        write_comm(&miso, input);
    }
}

void *t_server(void* params){
    
}

void *t_client(void* params){
    
}

void write_comm(char*** ch, char* in){
    //while(in_use(*ch, 1));              //wait until the selected channel of communication is not in use, then set it to 1, flagging it as used
    if(strcmp("", (*ch)[SIZE-1]) == 0){
        shift(ch, SIZE);
        strcpy((*ch)[0], in);
    }
    else{
        //TODO: too small stack size -> exception
    }
    //in_use(*ch, 0);
}

int read_comm(char*** ch, char* out){
    short i = SIZE - 1 ;
    //while(in_use(*ch, 1));              //wait until the selected channel of communication is not in use, then set it to 1, flagging it as used

    while(strcmp("", (*ch)[i]) == 0 && i>0) i--;
    if(strcmp("", (*ch)[i]) != 0){
        strcpy(out, (*ch)[i]);
        strcpy((*ch)[i], "");
        return 1;
    }
    else{
        //TODO: too small stack size -> exception
    }
    return 0;
    //in_use(*ch, 0);
}