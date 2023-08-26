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

enum State {working, stoping}; 

class ManagerThread {
private:
    std::mutex buffer_mutex;
    std::queue<std::string> buffer;        /* Allows multiple messages to be saved when breaking a socket */
    enum State work_status;
    Client client;
    Semafore semafore;
    void getStrByConsole();
    void sendStrByClient();
    void setStrInBuffer(std::string& str);
    std::string getStrByBuffer();

public:
    ManagerThread();
    void startThreads();
};

