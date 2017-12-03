#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <stdlib.h>
#include "../../text/headers/json.h"
#include "../../text/headers/base64.h"

#define LOGFILE "html_log.table"
#define HTML_BEGIN "<html><head><title>Info</title></head><body><table tyle=\"width:100%%\"><tr><th>Type</th><th>Client</th><th>message</th></tr>"
#define HTML_END   "</table></body></html>"
#define HEADER "HTTP/1.1 200 OK\nUser-agent: encrypto-0.1.0\nContent-Type: text/html\nContent-Length: "
#define KEYLEN 256

void log_file(char* , char* , char*);
char* read_key(char*);
char* load_log();
void write_pem(const char* , char* , const char*);

#endif