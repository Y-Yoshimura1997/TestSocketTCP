#include "SocketClient.h"

SocketClient::SocketClient(const char* ip_server, int port_server)
{   
    signal(SIGPIPE,SIG_IGN);
    
    addr_server_.sin_addr.s_addr = inet_addr(ip_server);
    addr_server_.sin_port        = htons(port_server);
    addr_server_.sin_family      = AF_INET;

    timeout_.tv_sec  = 1;  
    timeout_.tv_usec = 0;
}



void SocketClient::Connect()
{

    fd_socket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (fd_socket_ != -1) {
        std::cout << "> Create Socket FD:" << fd_socket_ << std::endl;
        setsockopt(fd_socket_, SOL_SOCKET, SO_RCVTIMEO, &timeout_, sizeof(timeout_));
        
    } else
    {
        std::cout << "> Failed to Create Socket" << std::endl;
    }

    for (;;){
        int is_connect = connect(fd_socket_, (struct sockaddr *)&addr_server_, addr_len_);
        if (is_connect != -1)
        {
            std::cout << "Connected to Server" << std::endl;
            break;
        } else {
            std::cout << "Failed to Connect" << std::endl;
        }
    }

    getsockname(fd_socket_, (struct sockaddr *)&addr_client_, &addr_len_);
    std::cout << "> Server Info" << std::endl;
    AddrInfo(addr_server_);
    std::cout << "> Client Info" << std::endl;
    AddrInfo(addr_client_);

};



void SocketClient::SendText(const char* text)
{
    int send_byte =  send(fd_socket_, text, std::strlen(text), 0);
    if(send_byte < 0){
        std::cout << "Disconnected"<< std::endl;
        Connect();
    }else if(send_byte == 0){
        std::cout << "Failed to Send"<< std::endl;
    }
};



void SocketClient::RecvText(char* text)
{
    int recv_byte = recv(fd_socket_, text, 1024, 0);
    if (recv_byte < 0) 
    {
        std::cout << "Disconnected"<< std::endl;
        text[0] = '\0';
    } else if(recv_byte == 0){
        std::cout << "Failed to Recive"<< std::endl;
        text[0] = '\0';
    } else {
        text[recv_byte] = '\0';
    }
};


void SocketClient::AddrInfo(struct sockaddr_in addr)
{
    std::cout << "  ip   : " << inet_ntoa(addr.sin_addr) << std::endl;
    std::cout << "  port : " << ntohs(addr.sin_port) << std::endl;
}