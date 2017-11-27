#include "headers/client.h"

extern char** n_miso;
extern char** n_mosi;
extern char* serverip;

int sock;

void* client(void* params)
{
    struct sockaddr_in server;
    char * message = (char*)malloc(sizeof(char)*MAX_ANSWER_SIZE);

    sock = socket(AF_INET , SOCK_STREAM , 0);
     
    server.sin_addr.s_addr = inet_addr(serverip);
    server.sin_family = AF_INET;
    server.sin_port = htons(PORTNUM+1);
 
    connect(sock , (struct sockaddr *)&server , sizeof(server));
 
    create_thread(c_callback, NULL);
    
    while(1)
    {
        if(read_comm(&n_mosi, &message)){
            handle_output(message);
        }
        nanosleep((const struct timespec[]){{0, 10000000L}}, NULL);
    }

}

void* c_callback(void* params)
{
    int size;
    char server_reply[MAX_RESPONSE_SIZE];
    while((size = recv(sock , server_reply , MAX_RESPONSE_SIZE , 0)) > 0)
    {
        server_reply[size] = '\0';
        handle_input(server_reply);
    }
}


void handle_output(char* out)
{
    char json[MAX_RESPONSE_SIZE];
    memset(json, 0, sizeof(char)*MAX_RESPONSE_SIZE);
    build_json(json, "type", "message");
    build_json(json, "sender", "Bela");
    build_json(json, "content", out);
    finalize(json);
    build_http(HEADER, json);
    send(sock, json, strlen(json), 0);
}

void handle_input(char* in)
{
    in = get_http(in);
    char value[MAX_ANSWER_SIZE], content[MAX_ANSWER_SIZE];
    get_value(in, "type", value);
    if(strcmp(value, "message") == 0)
    {
        get_value(in, "sender", value);
        get_value(in, "content", content);
        sprintf(in, "%s:\t\t%s\n", value, content);
        write_comm(&n_miso, in);        //We do not want to directly communicate with the interface, let the router thread take care of that
    }
}