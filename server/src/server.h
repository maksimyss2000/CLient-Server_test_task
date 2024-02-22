#pragma once 

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

constexpr auto PORT = 4001;
constexpr auto IP = "127.0.0.10";

enum class State {
    working,
    stopped,
};

class Server {
public:
    /// @brief server startup configuration implemented there
    Server();
    
    ~Server();

    /// @brief Checking the obtained data for compliance with the given conditions
    /// @param receive_sum data received in the socket (by convention is the sum of the digits in the string)
    void handleReceiveSum( int& receive_sum );

    /// @brief start the server's work on receiving connections
    void startWork();

private:
    int server_soket;
    int connecion_request_soket;
    State server_state;
    struct sockaddr_in server_address;
};
