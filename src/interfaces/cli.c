/*
void *t_cli(void* params){
    char* out = (char*)malloc(sizeof(char)*MAX_SIZE);
    short choose;
    setbuf(stdout, NULL); //to write out everything immediately
    allocate_str_array(&mosi, SIZE, MAX_SIZE);
    allocate_str_array(&miso, SIZE, MAX_SIZE);
    create_thread(t_cli_input); //Catch any inputs

    while(1){
        while(!read_comm(&mosi, out))sleep(10);
        printf("%s", out);
    }

    free_str_array(&mosi, SIZE);
    free_str_array(&miso, SIZE);
    free(out);
    free(input);
}


void *t_cli_input(void* params){
    input = (char*)malloc(sizeof(char)*MAX_SIZE);
    for(int j = 0; j<MAX_SIZE; j++)input[j] = '\0';
    int i = 0;
    
    while(1){
        while (!enable)sleep(10);                            //Wait for enable signal
        while('\n' != (input[i] = getchar()))i++;
        input[i] = '\0';
        write_comm(&miso, input);
        for(int j = 0; j<=i; j++)input[j] = '\0';
        i = 0;
        enable = 0;
    }
}*/