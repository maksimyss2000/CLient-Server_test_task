#ifndef SERVER_H
#define SERVER_H


#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <cstdio>
#include <cstring>


#define MY_PORT  4001
#define MY_IP    "127.0.0.10"
#define BUF_SIZE 150                       /* We assume that longer messages will be filtered out by program #1 */


class Server {
public:
                       Server();
                       ~Server();
    void               getMessage();
    void               handleMessage();

private:
    int                server;
    int                sock;
    char               buf[BUF_SIZE];
    std::string        message;
    struct sockaddr_in server_address;
};

#endif // SERVER_H
