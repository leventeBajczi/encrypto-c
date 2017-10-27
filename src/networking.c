#include "networking.h"

#define MAX_ANSWER_SIZE 3584    //3.5kiB for the body
#define MAX_RESPONSE_SIZE 4096  //4kiB for the entire message
#define HEADER "HTTP/1.1 200 OK\nUser-agent: encrypto-0.1.0\nContent-Type: text/html\nContent-Length: "

struct sockaddr_in client, server; //socket info about the client and the server
int socket_handle;


int get_next_message(char* msg){
    char* c = NULL;
    msg[0] = '\0';            
    build_json(msg, "type", "key");
    build_json(msg, "value", "my_secret_key");
    finalize(msg);
    return 1;
}

void init_server()
{
    char* resp = (char*)malloc(sizeof(char)*MAX_RESPONSE_SIZE);
    char* msg = (char*)malloc(sizeof(char)*MAX_ANSWER_SIZE);
    socklen_t socksize = sizeof(struct sockaddr_in);
    int consocket;

    memset(&server, 0, sizeof(server));          
    server.sin_family = AF_INET;                
    server.sin_addr.s_addr = htonl(INADDR_ANY); 
    server.sin_port = htons(PORTNUM);          //listen on the port defined above

    socket_handle = socket(AF_INET, SOCK_STREAM, 0);
  
    //start listening, allowing 1 concurrent connection
    bind(socket_handle, (struct sockaddr *)&server, sizeof(struct sockaddr));
    listen(socket_handle, 1);
    consocket = accept(socket_handle, (struct sockaddr *)&client, &socksize);
  
    while(consocket)
    {
        while(!get_next_message(msg))sleep(100);
        sprintf(resp, "%s %d\r\n\r\n%s\n\r\n", HEADER, strlen(msg) + 3, msg);
        printf("%s", resp);
        send(consocket, resp, strlen(resp), 0);
        close(consocket);
        consocket = accept(socket_handle, (struct sockaddr *)&client, &socksize);
    }
    printf("end");

}

void init_listener(){

}

void init_client()
{
    char buffer[MAX_ANSWER_SIZE+1]; //+1 for \0
    int len, mysocket;
    struct sockaddr_in dest; 
    char* resp = (char*)malloc(sizeof(char)*MAX_ANSWER_SIZE);
    char* msg = (char*)malloc(sizeof(char)*MAX_ANSWER_SIZE);
  
    mysocket = socket(AF_INET, SOCK_STREAM, 0);
   
    memset(&dest, 0, sizeof(dest));                /* zero the struct */
    dest.sin_family = AF_INET;
    dest.sin_addr.s_addr = htonl(INADDR_LOOPBACK); /* set destination IP number - localhost, 127.0.0.1*/ 
    dest.sin_port = htons(PORTNUM);                /* set destination port number */
  
    while(connect(mysocket, (struct sockaddr *)&dest, sizeof(struct sockaddr_in)))sleep(10);
   
    len = recv(mysocket, buffer, MAX_ANSWER_SIZE, 0);
  
    /* We have to null terminate the received data ourselves */
    buffer[len] = '\0';
  
    printf("Received %s (%d bytes).\n", (char*)(strchr(buffer, '\r')+4), strlen((char*)(strchr(buffer, '\r')+4)));  // Text after the first \r\n\r\n
  

    msg = "Hello world!";
    sprintf(resp, "%s %d\r\n\r\n%s\n\r\n", HEADER, strlen(msg) + 3, msg);
    printf("sending \n%s\n", resp);
    send(mysocket, resp, strlen(resp), 0);


    close(mysocket);
}