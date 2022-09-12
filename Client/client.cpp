#include "client.h"

Client::Client(){
    server_address.sin_port        = htons(MY_PORT);
    server_address.sin_family      = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(MY_IP);
    tryConnect();
}


Client::~Client(){
    close(sock);
}


void Client::tryConnect(){
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        /* @dbg */
        perror("Error init socket");
        exit(1);
    }
    while (connect(sock, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
        /* @dbg */
        //perror("connect");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

/*
 *  Send does not immediately catch an error if the socket is broken. Only when sending a second message.
 *  When looking for solutions to this problem, this one seems to be the most elegant.
 */
void Client::sendMessage(std::string& message){
    while (true) {
        bytes_count = send(sock, message.c_str(), message.length() + 1, MSG_NOSIGNAL);
        bytes_count = send(sock, NULL, 0, MSG_NOSIGNAL);    /* Catching brocken pepe. See comments above */
        if (bytes_count < 0 || errno == 32) {               /* MACRO errno == 32 if brocken pepe */
              /* @dbg */
              //perror("send");
              tryConnect();
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));    /* loss of messages when calling send() without delay */
            break;                                                         /* 3/4/5 or more messages within a second. */
        }                                                                  /* The situation is created when there are accumulated messages when reconnecting. */
    }
}
