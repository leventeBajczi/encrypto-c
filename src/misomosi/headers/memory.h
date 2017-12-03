#ifndef MEMORY_H
#define MEMORY_H

#include <stdlib.h>
#include <string.h>
#include "../../defines.h"

void allocate_str_array(char***, int, int);
void free_str_array(char***, int);
void shift(char***, int);
#endif