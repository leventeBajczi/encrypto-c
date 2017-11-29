#ifndef GUI_H
#define GUI_H

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#include "../../threads/headers/threads.h"
#include "../../misomosi/headers/misomosi.h"

void* gui(void*);
void send_clicked();
void* handler(void*);
#define MAX_RESPONSE_SIZE 4096

#endif