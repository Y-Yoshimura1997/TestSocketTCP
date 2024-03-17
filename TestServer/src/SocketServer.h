#include <iostream>
#include <cstring>
#include <stdio.h>
#include <thread>
#include <chrono>

#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>

class SocketServer
{
private:
    int fd_socket_;
    int fd_socket_new_;
    struct sockaddr_in addr_server_;
    struct sockaddr_in addr_client_;
    socklen_t addr_len_ = sizeof(struct sockaddr_in);
    
    int sock_port_; 
    struct timeval timeout_;

public:
    SocketServer(int port_server);
    void Connect();
    void SendText(const char* text);
    void RecvText(char* text);
    void AddrInfo(struct sockaddr_in addr);
};