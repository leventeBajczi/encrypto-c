#include "headers/client.h"

extern char** n_miso;
extern char** n_mosi;   

int mysocket;

void* client(void* params)
{

    struct sockaddr_in server; //socket info about the server
    char buffer[MAX_ANSWER_SIZE+1]; //+1 for \0
    int len;
    char* out;

    mysocket = socket(AF_INET, SOCK_STREAM, 0);
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;        //we want to have IP addresses as referrals
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); //Set the server's IP
    server.sin_port = htons(PORTNUM);   //the port we are trying to get through

    while(connect(mysocket, (struct sockaddr *)&server, sizeof(struct sockaddr_in)));

    //from here we have a connection to the server

    while(1)
    {
        if(read_comm(&n_mosi, out)) handle_output(out);
        if((len = recv(mysocket, buffer, MAX_ANSWER_SIZE, 0)) > 0)
        {
            buffer[len] = '\0';     //Null terminate, whatever happens (lost connection e.g.)
            handle_input(buffer);
        }
        sleep(10);  //we want to wait a bit not to occupy the CPU too much
    }

    close(mysocket);


}

void handle_output(char* out)
{
    char* str = malloc(sizeof(char)*MAX_RESPONSE_SIZE);
    strcpy(str, out);
    build_http(str);
    send(mysocket, str, strlen(str), 0);
    free(str);
}

void handle_input(char* in)
{
    in = get_http(in);
    write_comm(&n_miso, in);        //We do not want to directly communicate with the interface, let the main thread take care of that
}