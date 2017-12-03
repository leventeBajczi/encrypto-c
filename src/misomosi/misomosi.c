#include "headers/misomosi.h"

void write_comm(char*** ch, char* in){
    if(strcmp("", (*ch)[SIZE-1]) == 0){
        shift(ch, SIZE);
        strcpy((*ch)[0], in);
    }
}

int read_comm(char*** ch, char** out){
    short i = SIZE - 1 ;

    while(strcmp("", (*ch)[i]) == 0 && i>0) i--;
    if(strcmp("", (*ch)[i]) != 0){
        strcpy(*out, (*ch)[i]);
        strcpy((*ch)[i], "");
        return 1;
    }
    return 0;
}