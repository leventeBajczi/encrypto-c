#include "headers/client.h"

extern char** n_miso;
extern char** n_mosi;
extern char* serverip;
extern char* portnum;
extern char* connection;
extern char* name;

extern int running;

int sock;

void* client(void* params)
{
    struct sockaddr_in server;
    char * message = (char*)malloc(sizeof(char)*MAX_ANSWER_SIZE);

    sock = socket(AF_INET , SOCK_STREAM , 0);
     
    server.sin_addr.s_addr = inet_addr(serverip);
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(portnum));
 
    while(connect(sock , (struct sockaddr *)&server , sizeof(server)));
    connection = CONNECTION_CONNECTED;
    send_connected();
 
    create_thread(c_callback, NULL);
    
    while(running)
    {
        if(read_comm(&n_mosi, &message)){
            handle_output(message);
        }
        nanosleep((const struct timespec[]){{0, 10000000L}}, NULL);
    }
    free(message);

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
    build_json(json, "sender", name);
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
        sprintf(in, "%s:\t\t%s", value, content);
        write_comm(&n_miso, in);        //We do not want to directly communicate with the interface, let the router thread take care of that
    }
    else if(strcmp(value, "status") == 0)
    {
        get_value(in, "sender", value);
        get_value(in, "content", content);
        sprintf(in, "%s%s", content, value);
        write_comm(&n_miso, in);        //We do not want to directly communicate with the interface, let the router thread take care of that
    }
}

void send_connected()
{
    char json[MAX_RESPONSE_SIZE];
    memset(json, 0, sizeof(char)*MAX_RESPONSE_SIZE);
    build_json(json, "type", "status");
    build_json(json, "sender", name);
    build_json(json, "content", "Connection successful from ");
    finalize(json);
    build_http(HEADER, json);
    send(sock, json, strlen(json), 0);
}