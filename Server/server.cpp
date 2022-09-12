#include "server.h"


Server::Server(){
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
       perror("Error init socket");
       exit(1);
    }

    server_address.sin_port        = htons(MY_PORT);
    server_address.sin_family      = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(MY_IP);
    if (bind(sock, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
        perror("Error bind");
        exit(2);
    }
}


Server::~Server(){
    close(server);
}


void Server::getMessage(){
    int bytes_read;
    listen(sock, 1);
    while (true) {
        server = accept(sock, NULL, NULL);
        if (server < 0) {
            std::cout << "Error accept" << std::endl;
        }
        while (true) {
            bytes_read = recv(server, buf, BUF_SIZE, 0);
            if (bytes_read == 0) {
                std::cout << "The sender closed the connection" << std::endl;
                break;
            }
            if (bytes_read < 0 ) {
                perror("Error recv socket");
            }
            message = std::string(buf);    /* for unification c++ style */
            handleMessage();
        }
    }
}


void  Server::handleMessage(){
    std::cout << "get message:" << message << std::endl;
    int len = message.length();
    int sum = stoi(message);
    if (len > 2 && sum%32 == 0) {
        std::cout << "No error detected" << std::endl;
    } else {
        std::cout << "Error get data" << std::endl;
    }
}

