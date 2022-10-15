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

void ChatServer::messageReceiveThreadWorker()
{
    int i;
    std::cout << "command list : helpl num user, num_chat, ip_list" << std::endl;
	while (1) {
		char bufmsg[MAXLINE + 1];
		fprintf(stderr, "\033[1;32m"); 
		printf("server>");
		fgets(bufmsg, MAXLINE, stdin); 
		if (!strcmp(bufmsg, "\n")) continue;  
		else if (!strcmp(bufmsg, "help\n")) 
        {
            std::cout << "help, num_user, num_chat, ip_list" << std::endl;
        }   
		else
        {
            std::cout << "worng command. help check" << std::endl;
        }
	}
}

void ChatServer::executeCommandListener()
{
	cm_listener = std::thread(ChatServer::messageReceiveThreadWorker);
	cm_listener.detach();
}

void ChatServer::joinCommandListener()
{
	if(cm_listener.joinable())
	{
		cm_listener.join();
	}
}

int main(int argc, char *argv[]) 
{
	struct sockaddr_in cliaddr;
	char buf[MAXLINE + 1]; //클라이언트에서 받은 메시지
	int i, j, nbyte, accp_sock, addrlen = sizeof(struct sockaddr_in);
	fd_set read_fds;	//읽기를 감지할 fd_set 구조체
	ChatServer server;
	pthread_t a_thread;

	if (argc != 2) 
    {
		printf("사용법 :%s port\n", argv[0]);
        std::cout << "usage :" + std::string(argv[0]) + "port" << std::endl;
		exit(0);
	}
	server.openSocket();
	server.readyServer();
	server.executeCommandListener();
	while(1);
	server.joinCommandListener();

	return 0;
}