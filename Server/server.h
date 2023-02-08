#ifndef SERVER_H
#define SERVER_H


#include <iostream>
#include <thread>
#include <cstdio>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


#define DEFAULT_PORT  4001
#define DEFAULT_IP    "127.0.0.10"
#define BUF_SIZE      150                  /* We assume that longer messages will be filtered out by program #1 */


class Server {
public:
                       Server(int argc, char *argv[]);
                       ~Server();
    void               getMessage();
    void               handleMessage();
    void               recognizeArgument(int argc, char *argv[]);

private:
    int                server;
    int                sock;
    int                port;
    char               buf[BUF_SIZE];
    std::string        ip;
    std::string        message;
    struct sockaddr_in server_address;
};

#endif // SERVER_H
