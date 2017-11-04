#include "headers/server.h"

extern char** n_miso;

void* server(void* params)
{
    char buffer[MAX_ANSWER_SIZE+1]; //+1 for \0
    struct sockaddr_in client, server; //socket info about the client and the server
    int socket_handle, len;

    socklen_t socksize = sizeof(struct sockaddr_in);
    int consocket;

    memset(&server, 0, sizeof(server));          
    server.sin_family = AF_INET;                
    server.sin_addr.s_addr = htonl(INADDR_ANY); 
    server.sin_port = htons(PORTNUM);

    socket_handle = socket(AF_INET, SOCK_STREAM, 0);

    bind(socket_handle, (struct sockaddr *)&server, sizeof(struct sockaddr));
    listen(socket_handle, 1);
    consocket = accept(socket_handle, (struct sockaddr *)&client, &socksize);
  
    while(consocket)
    {
        while(1){
            if((len = recv(socket_handle, buffer, MAX_ANSWER_SIZE, 0)) > 0)
            {
                buffer[len] = '\0';     //Null terminate, whatever happens (lost connection e.g.)
                handle_input(buffer);
            }
        }
        close(consocket);
        consocket = accept(socket_handle, (struct sockaddr *)&client, &socksize);
    }
    close(consocket);

}

void handle_input(char* in)
{
    in = get_http(in);
    write_comm(&n_miso, in);        //We do not want to directly communicate with the interface, let the main thread take care of that
    //TODO: send to all other clients currently connected 
}