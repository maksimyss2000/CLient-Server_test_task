#include "client.h"


Client::Client(int argc, char *argv[]){
    recognizeArgument(argc, argv);
    server_address.sin_port        = htons(port);
    server_address.sin_family      = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(ip.c_str());
    tryConnect();
}


Client::~Client(){
    close(sock);
}


/*TODO: make a handle invalid arguments and check the port and IP*/
void Client::recognizeArgument(int argc, char *argv[]){ 
    if (argc == 2 && !strcmp(argv[1], "-h")) {
        std::cout << "Usage: server.out [IP] [PORT]\n"
                     "With no IP and no PORT, use default PORT and default IP\n";
        exit(0);
    }
    if (argc >= 3) {
        ip   = argv[1];
        port = atoi(argv[2]);
    } else {
        ip   = DEFAULT_IP;
        port = DEFAULT_PORT;
    }
}


void Client::tryConnect(){
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        /* @dbg */
        //perror("Error init socket");
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
        }                                                                  /* The situation is created when there are accumulated messages during the reconnecting. */
    }
}
