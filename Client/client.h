#ifndef CLIENT_H
#define CLIENT_H


#include <iostream>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include <string>
#include <chrono>

#define MY_PORT  4001
#define MY_IP    "127.0.0.10"
#define BUF_SIZE 150


class Client {
private:
    int                sock;
    int                bytes_count;
    struct sockaddr_in server_address;
    void               tryConnect();

public:
                       Client();
                       ~Client();
    void               sendMessage(std::string& message);
};

#endif // CLIENT_H
