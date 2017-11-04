#include "headers/misomosi.h"

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
        out = (char*)realloc(out, sizeof(char) * (strlen((*ch)[i]) + 1));
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