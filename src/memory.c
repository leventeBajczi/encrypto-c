#include "memory.h"

void allocate_str_array(char*** array, int size, int piece_size){
    *array = (char**)malloc(sizeof(char*)*size);
    for(int i = 0; i<size; i++){
        (*array)[i] = (char*)malloc(sizeof(char)*piece_size);
        strcpy((*array)[i], "");
    }
    return;
}
void shift(char*** array, int size){
    for(int i = size-1; i>0; i--) strcpy((*array)[i], (*array)[i-1]);
    strcpy((*array)[0], ""); 
}