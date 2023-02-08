#include "server.h"


Server::Server(int argc, char *argv[]){
    recognizeArgument(argc, argv);
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
       perror("Error init socket");
       exit(1);
    }

    server_address.sin_port        = htons(port);
    server_address.sin_family      = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(ip.c_str());
    if (bind(sock, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
        perror("Error bind");
        exit(2);
    }
}


Server::~Server(){
    close(server);
}


/*TODO: make a handle invalid arguments and check the port and IP*/
void Server::recognizeArgument(int argc, char *argv[]){ 
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
    if (len > CONDITION_MAX_LENGHT && sum % CONDITION_DIVIDER == 0) {
        std::cout << "Error wasn't detected" << std::endl;
    } else {
        std::cout << "Error get data" << std::endl;
    }
}
