#pragma once 

#include <iostream>
#include <thread>
#include <chrono>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

constexpr auto PORT = 4001;
constexpr auto IP = "127.0.0.10";

class Client {
private:
    int sock;
    struct sockaddr_in server_address;
    void tryConnect();

public:
    Client();
    ~Client();
    void sendInteger(const int& integer);
};

