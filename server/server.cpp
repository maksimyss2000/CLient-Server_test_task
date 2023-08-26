#include "server.h"

constexpr auto CONDITION_DIVIDER = 32;
constexpr auto CONDITION_MAX_LENGHT = 2;

Server::Server() {
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        /* @dbg */
        //perror("Error init socket");
        exit(EXIT_FAILURE);
    }

    /*TODO: to think about putting it in a separate function. */
    server_address.sin_port = htons(PORT);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(IP);

    if (bind(sock, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
        /* @dbg */
        //perror("Error bind");
        exit(EXIT_FAILURE);
    }
}

Server::~Server() {
    close(server);
}
 
void Server::startWork() {
    std::cout << "server has been started at " << IP << ":" << PORT << std::endl;

    int receive_sum;
    int bytes_read;
    listen(sock, 1);
    while (true) {
        server = accept(sock, NULL, NULL);
        if (server < 0) {
            std::cout << "Error accept" << std::endl;
        }
        while (true) {
            bytes_read = recv(server, &receive_sum, sizeof(receive_sum), 0);
            if (bytes_read == 0) {
                std::cout << "The sender closed the connection" << std::endl;
                break;
            }
            if (bytes_read < 0 ) {
                /* @dbg */
                //perror("Error recv socket");
            }
            
            handleReceiveSum(receive_sum);
        }
    }
}

/* can find the length through the log10(), but solution by use string seems more readable */
void  Server::handleReceiveSum(int& receive_sum) {
    std::cout << "get sum:" << receive_sum << std::endl;
    std::string sum_by_str = std::to_string(receive_sum); 

    if (sum_by_str.length() > CONDITION_MAX_LENGHT && receive_sum % CONDITION_DIVIDER == 0) {
        std::cout << "Error wasn't detected" << std::endl;
    } else {
        std::cout << "Error get data" << std::endl;
    }
}
