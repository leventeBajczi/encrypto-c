#include "headers/server.h"

extern char** n_miso;
extern char** c_mosi;

int *sockets;
int socketnumber = 0;

void* server(void* params)
{
    int socket_dest , client_sock , c;
    struct sockaddr_in sockserver , client;
    sockets = (int*)malloc(sizeof(int)*CONCURR_CLIENTS);
     
    socket_dest = socket(AF_INET , SOCK_STREAM , 0);

    sockserver.sin_family = AF_INET;
    sockserver.sin_addr.s_addr = INADDR_ANY;
    sockserver.sin_port = htons(PORTNUM);
    create_thread(callback, NULL);
    while(1){    
        bind(socket_dest,(struct sockaddr *)&sockserver , sizeof(sockserver));

        listen(socket_dest , 1);
        
        c = sizeof(struct sockaddr_in);
        
        client_sock = accept(socket_dest, (struct sockaddr *)&client, (socklen_t*)&c);
        
        create_thread(serverread, (void*)&client_sock);
        
    }     

}

void* serverread(void* params)
{
    int read_size;
    int socket = ((int*)params)[0];
    char client_message[MAX_RESPONSE_SIZE];
    sockets[socketnumber] = socket;
    socketnumber++;
    while(1)
    {
            read_size = recv(socket, client_message , MAX_RESPONSE_SIZE , 0);
            client_message[read_size] = '\0';
            s_handle_input(client_message);
    }
}

void s_handle_input(char* in)
{
    in = get_http(in);
    write_comm(&n_miso, in);        //We do not want to directly communicate with the interface, let the main thread take care of that
    write_comm(&c_mosi, in);
}

void* callback(void* params)
{
    char *msg = (char*)malloc(sizeof(char)*MAX_ANSWER_SIZE);

    while(1)
    {
        if(read_comm(&c_mosi, msg))
        {
            for(int i = 0; i<socketnumber; i++)
            {
                send(sockets[i], msg, strlen(msg), 0);
            }
        }
    }
}