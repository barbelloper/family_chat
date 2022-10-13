#ifndef CHAT_SERVER_
#define CHAT_SERVER_
#include <iostream> // c++ stadard input output
#include <vector> //vector
#include <utility> //pair
#include <thread> //thread
#include <cstdlib>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>

#define PORT 8080 
#define PACKET_SIZE 1024

class ChatServer
{
private:
    typedef int32_t socket_t;
    typedef struct client_t
    {
       socket_t client;
       struct sockaddr client_addr = {0,};
       int client_size = sizeof(client_addr);
       int number = -1;
    } client_t;

    typedef std::pair<client_t, std::string> pii;
    socket_t socket_fd;
    struct sockaddr_in server_addr;
    std::vector<pii> client_info;
    bool is_open_socket;
public:
    ChatServer(/* args */);
    ~ChatServer(); 
    int openSocket();
    int readyServer();
    void messageReceiveThreadWorker();
};

ChatServer::ChatServer(/* args */)
{
    socket_fd = -1;
    is_open_socket = false;
}

ChatServer::~ChatServer()
{
}

#endif