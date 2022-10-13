#include "chat_server.h"

int ChatServer::openSocket()
{
    int ret = -1;
    if (!is_open_socket)
    {
        ChatServer::socket_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (ChatServer::socket_fd >= 0)
        {
            is_open_socket = true;
            ret = 0;
        }
    }
    return ret;
}

int ChatServer::readyServer()
{
    int ret = -1;

    if (is_open_socket)
    {
        memset(&(ChatServer::server_addr), 0, sizeof(ChatServer::server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	    server_addr.sin_port = htons(PORT);
        if (bind(ChatServer::socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) 
        {
		   std::cout << "bind fail!" << std::endl;
        }
        else
        {
            listen(ChatServer::socket_fd, SOMAXCONN);
            ret = 0;
        }
    }
    return ret;
}

int main() 
{ 

}