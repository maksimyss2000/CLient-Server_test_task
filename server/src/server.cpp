#include "server.h"

#include <iostream>
#include <unistd.h>

constexpr auto MAX_CONNECT_QUEUE = 1;
constexpr auto CONDITION_DIVIDER = 32;
constexpr auto CONDITION_MAX_LENGHT = 2;

Server::Server()
{
    server_soket = socket( AF_INET, SOCK_STREAM, 0 );
    if ( server_soket < 0 )
    {
        perror("Error init socket");
        exit(EXIT_FAILURE);
    }

    /*TODO: to think about putting it as a separate feature. */
    server_address.sin_port = htons( PORT );
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr( IP );

    if ( bind( server_soket, (struct sockaddr *) &server_address, sizeof( server_address ) ) < 0 )
    {
        perror("Error bind");
        exit(EXIT_FAILURE);
    }

    server_state = State::working;
}

Server::~Server() 
{
    close( server_soket );
}

void Server::startWork() 
{
    std::cout << "server has been started at " << IP << ":" << PORT << std::endl;

    int bytes_read;
    int receive_sum;

    listen ( server_soket, MAX_CONNECT_QUEUE );
    while ( server_state == State::working ) 
    {
        connecion_request_soket = accept( server_soket, nullptr, nullptr );
        if ( connecion_request_soket < 0 ) 
        {
            perror("Error accept");
        }
        while ( true ) {
            bytes_read = recv( connecion_request_soket, &receive_sum, sizeof( receive_sum ), 0 );
            if ( bytes_read == 0 ) 
            {
                std::cout << "Sender disconnected" << std::endl;
                break;
            }
            if ( bytes_read < 0 ) 
            {
                perror("Error recv socket");
                break;
            }
            
            handleReceiveSum( receive_sum );
        }
    }
}

void  Server::handleReceiveSum( int& receive_sum ) {
    std::cout << "get sum:" << receive_sum << std::endl;

    std::string sum_by_str{ std::to_string(receive_sum) }; 

    if ( sum_by_str.length() > CONDITION_MAX_LENGHT &&         /* can use receive_sum < 100, but this solution looks more readable */ 
         receive_sum % CONDITION_DIVIDER == 0 ) 
    {
        std::cout << "Error wasn't detected" << std::endl;
    } 
    else 
    {
        std::cout << "Error get data" << std::endl;
    }
}
