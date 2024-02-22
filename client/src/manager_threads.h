#pragma once 

#include <iostream>
#include <mutex>
#include <thread>
#include <string>
#include <queue>
#include <algorithm>
#include <semaphore>

#include "client.h"
#include "semafore.h"

enum State { working, stoping }; 

/// @brief It is used to solve the problem of interaction of data acquisition and data processing processes
/// @details typical produser-consumer solution 
class ManagerThread {
private:
    std::mutex buffer_mutex;
    std::queue<std::string> buffer;        /* Allows multiple messages to be saved when breaking a socket */
    enum State work_status;
    Client client;
    Semafore semafore;

    /// @brief get a message from the console to the sending server, and buffer it in a potentially infinite loop.
    /// @details main produser logic
    void getMessageProcess();

    /// @brief get message from buffer and send to server
    /// @details main consumer logic
    void sendStrByClient();
    
    /// @brief Atomic get string from buffer
    std::string getStrByBuffer();

    /// @brief Atomic set string to buffer
    /// @param str New data for record to end of buffer
    void setStrInBuffer( std::string& str );

public:
    ManagerThread();
    /// @brief start main produser  and consumer threads
    void startThreads();
};

