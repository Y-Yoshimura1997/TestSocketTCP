#include "SocketServer.h"

SocketServer::SocketServer(int port_server)
{   
    signal(SIGPIPE,SIG_IGN);

    addr_server_.sin_addr.s_addr = INADDR_ANY;
    addr_server_.sin_port        = htons(port_server);
    addr_server_.sin_family      = AF_INET;
    sock_port_ = port_server;
    
    timeout_.tv_sec  = 1; 
    timeout_.tv_usec = 0;


    fd_socket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (fd_socket_ != -1) {
        std::cout << "Create Socket FD:" << fd_socket_ << std::endl;
    } else
    {
        std::cout << "Failed to Create Socket" << std::endl;
    }
    
    int is_bind = bind(fd_socket_, (sockaddr*)&addr_server_, sizeof(addr_server_));
    if (is_bind != -1) {
        std::cout << "Bind FD:" << std::endl; 
    } else {
        std::cout << "Failed to Bind" << std::endl;
    }

};

void SocketServer::Connect()
{
    for (;;){
        int is_listen = listen(fd_socket_, SOMAXCONN);
        if (is_listen != -1) {
            std::cout << "Listen" << std::endl;
        } else {
            std::cout << "Failed to Listen" << std::endl;
        }
        fd_socket_new_ = accept(fd_socket_, (struct sockaddr *)&addr_client_, &addr_len_); 
        if (fd_socket_new_ != -1) {
            setsockopt(fd_socket_new_, SOL_SOCKET, SO_RCVTIMEO, &timeout_, sizeof(timeout_));
            std::cout << "Accepted FD:" << fd_socket_new_ << std::endl;
            break;
        } else {
            std::cout << "Failed to Accept"  << std::endl;
        }
    }
    
    getsockname(fd_socket_new_, (struct sockaddr *)&addr_server_, &addr_len_);
    std::cout << "> Server Info" << std::endl;
    AddrInfo(addr_server_);
    std::cout << "> Client Info" << std::endl;
    AddrInfo(addr_client_);

};

void SocketServer::SendText(const char* text)
{
    int send_byte =  send(fd_socket_new_, text, std::strlen(text), 0);
    if(send_byte < 0){
        std::cout << "Disconnected"<< std::endl;
        Connect();
    }else if(send_byte == 0){
        std::cout << "Failed to Send"<< std::endl;
    }
};



void SocketServer::RecvText(char* text)
{
    int recv_size = recv(fd_socket_new_, text, 1024, 0);
    if (recv_size < 0) 
    {
        std::cout << "Disconnected"<< std::endl;
        text[0] = '\0';
    } else if(recv_size == 0){
        std::cout << "Failed to Recive"<< std::endl;
        text[0] = '\0';
    } else {
        text[recv_size] = '\0';
    }
};


void SocketServer::AddrInfo(struct sockaddr_in addr)
{
    std::cout << "  ip   : " << inet_ntoa(addr.sin_addr) << std::endl;
    std::cout << "  port : " << ntohs(addr.sin_port) << std::endl;
}