#include "networking.h"

#define MAX_ANSWER_SIZE 512
#define HEADER "HTTP/1.1 200 OK\nUser-agent: encrypto-0.1.0\nContent-Type: text/html\nContent-Length: "

void init_server()
{
    char* resp = (char*)malloc(sizeof(char)*MAX_ANSWER_SIZE);
    char* msg = (char*)malloc(sizeof(char)*MAX_ANSWER_SIZE);
  
    struct sockaddr_in client, server; //socket info about the client and the server
    int socket_handle;
    socklen_t socksize = sizeof(struct sockaddr_in);

    memset(&server, 0, sizeof(server));          
    server.sin_family = AF_INET;                
    server.sin_addr.s_addr = htonl(INADDR_ANY); 
    server.sin_port = htons(PORTNUM);          //listen on the port defined above

    socket_handle = socket(AF_INET, SOCK_STREAM, 0);
  
    //start listening, allowing 1 concurrent connection
    bind(socket_handle, (struct sockaddr *)&server, sizeof(struct sockaddr));
    listen(socket_handle, 1);
    int consocket = accept(socket_handle, (struct sockaddr *)&client, &socksize);
  
    while(consocket)
    {
        msg = "Hello world!";
        sprintf(resp, "%s %d\r\n\r\n%s\n\r\n", HEADER, strlen(msg) + 3, msg);
        printf("Incoming connection from %s - sending \n%s\n", inet_ntoa(client.sin_addr), resp);
        send(consocket, resp, strlen(resp), 0);
        close(consocket);
        printf("\nclosed\n");
        consocket = accept(socket_handle, (struct sockaddr *)&client, &socksize);
    }

    close(socket_handle);
}