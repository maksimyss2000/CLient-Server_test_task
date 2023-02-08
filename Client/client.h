#ifndef CLIENT_H
#define CLIENT_H


#include <iostream>
#include <cstring>
#include <thread>
#include <string>
#include <chrono>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define DEFAULT_PORT   4001
#define DEFAULT_IP     "127.0.0.10"


class Client {
private:
    int                sock;
    int                bytes_count;
    int                port;
    struct sockaddr_in server_address;
    std::string        ip;
    void               tryConnect();
    void               recognizeArgument(int argc, char *argv[]);

public:
                       Client(int argc, char *argv[]);
                       ~Client();
    void               sendMessage(std::string& message);
};

#endif // CLIENT_H
