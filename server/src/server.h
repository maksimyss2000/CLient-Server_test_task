#pragma once 

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

constexpr auto PORT = 4001;
constexpr auto IP = "127.0.0.10";

class Server {
public:
    Server();
    ~Server();
    void handleReceiveSum(int& receive_sum);
    void startWork();

private:
    int server;
    int sock;
    struct sockaddr_in server_address;
};
