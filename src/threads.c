#include "threads.h"

char** mosi; 
char** miso;

pthread_t handles[5];
short count = 0;
char* input; 

pthread_t* create_thread(void* thread){
    pthread_create(&(handles[count]), NULL, thread, NULL);
    return &(handles[count++]);
}

void *t_cli(void* params){
    setbuf(stdout, NULL); //to write out everything immediately
    allocate_str_array(&mosi, SIZE, MAX_SIZE);
    allocate_str_array(&miso, SIZE, MAX_SIZE);
    create_thread(t_cli_input); //Catch any inputs
    char* out = (char*)malloc(sizeof(char)*MAX_SIZE);
    while(1){
        if(read_comm(&miso, out)){
            printf("\0337\033[2A\r\033[KYou:\t\t%s\n\0338", out);
            printf("\0337\033[1A\r\033[K%s\n\0338", EMPTYLINE);
        }
    }
}


void *t_cli_input(void* params){
    input = (char*)malloc(sizeof(char)*MAX_SIZE);
    for(int j = 0; j<MAX_SIZE; j++)input[j] = '\0';
    int i = 0;
    while(1){
        while('\n' != (input[i] = getchar())) i++;
        input[i] = '\0';
        
        write_comm(&miso, input);
        for(int j = 0; j<=i; j++)input[j] = '\0';
        i = 0;
    }
}

void *t_server(void* params){
    
}

void *t_client(void* params){
    char* helper = (char*)malloc(sizeof(char)*MAX_SIZE);
    while(1){
        sleep(2);
        strcpy(helper, input);
        printf("\0337\033[1A\rNot you:\t%sasdasd\0338\r%s\n", helper, EMPTYLINE);    //TODO: why doesnt it have the correct value..? 
    }
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