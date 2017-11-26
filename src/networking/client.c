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
    server.sin_port = htons(PORTNUM);
 
    connect(sock , (struct sockaddr *)&server , sizeof(server));
 
    create_thread(c_callback, NULL);
    
    while(1)
    {
        int size;
        if(read_comm(&n_mosi, message)){
            handle_output(message);
        }
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
    build_http(HEADER, out);
    send(sock, out, strlen(out), 0);
}

void handle_input(char* in)
{
    in = get_http(in);
    write_comm(&n_miso, in);        //We do not want to directly communicate with the interface, let the main thread take care of that
}