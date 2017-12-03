#ifndef DEFINES_H
#define DEFINES_H


#define LOGFILE "html_log.table"
#define HTML_BEGIN "<html><head><title>Info</title></head><body><table tyle=\"width:100%%\"><tr><th>Type</th><th>Client</th><th>message</th></tr>"
#define HTML_END   "</table></body></html>"
#define HEADER "HTTP/1.1 200 OK\nUser-agent: encrypto-0.1.0\nContent-Type: text/html\nContent-Length: "
#define KEYLEN 256
#define MAX_RESPONSE_SIZE MAX_SIZE

#define CLI_INTERFACE         "cli"
#define GUI_INTERFACE         "gui"

/* for CLI parameters and to specify their defaults - one-instruction startup is possible */ 
#define MODE_SWITCH         "-m"
#define CLIENT_SWITCH       "-c"
#define KEYS_SWITCH         "-k"
#define DIRECTORY_SWITCH    "-d"
#define SERVER_SWITCH       "-s"
#define NAME_SWITCH         "-n"
#define PORT_SWITCH         "-p"

#define DEFAULT_MODE        "client"
#define DEFAULT_CLIENT      "cli"
#define DEFAULT_KEYS        "./keyfiles"
#define DEFAULT_DIRECTORY   "./messages"
#define DEFAULT_SERVER      "127.0.0.1"
#define DEFAULT_NAME        "Anon"
#define DEFAULT_PORT        "0"
#define DEFAULT_CONNECTION  "Not connected"
#define DEFAULT_PARTNER   "-"

#define SIZE 16         //max size of communication between the master and the slave
#define MAX_SIZE 4096   //max size of each message between the master and the slave

#define MAX_ANSWER_SIZE 3584    //3.5kiB for the body
#define HEADER "HTTP/1.1 200 OK\nUser-agent: encrypto-0.1.0\nContent-Type: text/html\nContent-Length: "
#define AES_KEYLEN 32
#define CONNECTION_CONNECTED "Connected"
#define CONCURR_CLIENTS 5

#define CLIENT_MODE         "client"
#define SERVER_MODE         "server"

#define MODE 1      //from /dev/urandom, the safest one


#endif