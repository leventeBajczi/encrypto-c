#include "headers/server.h"

extern char** n_miso;
extern char** s_fifo;

extern char* portnum;

extern int running;

int *sockets;
int socketnumber = 0;

void* server(void* params)
{
    char writeout[25];
    int socket_dest , client_sock , c;
    struct sockaddr_in sockserver , client;
    sockets = (int*)malloc(sizeof(int)*CONCURR_CLIENTS);
     
    socket_dest = socket(AF_INET , SOCK_STREAM , 0);

    sockserver.sin_family = AF_INET;
    sockserver.sin_addr.s_addr = INADDR_ANY;
    sockserver.sin_port = htons(atoi(portnum));
    create_thread(callback, NULL);
    while(running){    
        bind(socket_dest,(struct sockaddr *)&sockserver , sizeof(sockserver));

        listen(socket_dest , 1);
        c = sizeof(struct sockaddr_in);
        getsockname(socket_dest,(struct sockaddr *)&sockserver , (socklen_t*)&c);
        sprintf(writeout, "Listening on port: %d\n", ntohs(sockserver.sin_port));        
        write_comm(&n_miso, writeout);
        
        client_sock = accept(socket_dest, (struct sockaddr *)&client, (socklen_t*)&c);
        
        create_thread(serverread, (void*)&client_sock);
        
    }   
    free(sockets);  
}

void* host_info(void* params)
{
    char msg[MAX_ANSWER_SIZE];
    char* page;
  
    struct sockaddr_in dest; 
    struct sockaddr_in serv; 
    int mysocket;            
    socklen_t socksize = sizeof(struct sockaddr_in);

    memset(&serv, 0, sizeof(serv));           
    serv.sin_family = AF_INET;                
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
    serv.sin_port = htons(0);           

    mysocket = socket(AF_INET, SOCK_STREAM, 0);
  
    
    bind(mysocket, (struct sockaddr *)&serv, sizeof(struct sockaddr));

    listen(mysocket, 1);
    getsockname(mysocket,(struct sockaddr *)&serv , &socksize); 
    sprintf(msg, "Info available on port %d", ntohs(serv.sin_port));  
    write_comm(&n_miso, msg);
    int consocket = accept(mysocket, (struct sockaddr *)&dest, &socksize);
  
    while(consocket)
    {
        page = load_log();
        build_http(HEADER, page);
        send(consocket, page, strlen(page), 0); 
        close(consocket);
        getsockname(mysocket,(struct sockaddr *)&serv , &socksize);    
        sprintf(msg, "Info available on port %d", ntohs(serv.sin_port));  
        write_comm(&n_miso, msg);
        consocket = accept(mysocket, (struct sockaddr *)&dest, &socksize);
        free(page);
    }
    free(page);
    close(mysocket);
}


void* serverread(void* params)
{
    int read_size;
    int socket = ((int*)params)[0];
    char client_message[MAX_RESPONSE_SIZE];
    struct sockaddr_in socketaddr;
    int c;
    struct in_addr ip;
    char str[16];
            
    
    sockets[socketnumber] = socket;
    socketnumber++;
    while(running)
    {
            read_size = recv(socket, client_message , MAX_RESPONSE_SIZE , 0);
            if(read_size <= 0) return NULL;
            client_message[read_size] = '\0';
            getsockname(socket,(struct sockaddr *)&socketaddr , (socklen_t*)&c);
            inet_ntop( AF_INET, &(socketaddr.sin_addr), str, INET_ADDRSTRLEN );
            log_file("received", str, client_message);
            s_handle_input(client_message);
    }
}

void s_handle_input(char* in)
{
    in = get_http(in);
    write_comm(&n_miso, in);        //We do not want to directly communicate with the interface, let the main thread take care of that
    write_comm(&s_fifo, in);
}

void* callback(void* params)
{
    char *msg = (char*)malloc(sizeof(char)*MAX_RESPONSE_SIZE);

    while(running)
    {
        if(read_comm(&s_fifo, &msg))
        {
            struct sockaddr_in socket;
            int c;
            struct in_addr ip;
            char str[16];
            msg = realloc(msg, sizeof(char)*MAX_RESPONSE_SIZE);
            build_http(HEADER, msg);
                
            for(int i = 0; i<socketnumber; i++)
            {
                if(sockets[i] == 1)continue;
                getsockname(sockets[i],(struct sockaddr *)&socket , (socklen_t*)&c);
                if(socket.sin_zero)
                ip = socket.sin_addr;
                inet_ntop( AF_INET, &ip, str, INET_ADDRSTRLEN );
                log_file("sent", str, msg);
                if(send(sockets[i], msg, strlen(msg), 0)<0)sockets[i] = 1;
            }
        }
        nanosleep((const struct timespec[]){{0, 10000000L}}, NULL);
    }
    free(msg);
}
