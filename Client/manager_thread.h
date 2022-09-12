#ifndef MANAGER_THREAD_H
#define MANAGER_THREAD_H


#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <string>
#include <list>
#include <chrono>
#include<bits/stdc++.h>
#include <cstddef>

#include "semafore.h"
#include "client.h"


class ManagerThread {
private:
    std::list<std::string> buf;
    Client                 client;
    std::mutex             mutex;
    Semafore               semafore;
    std::string            input;
    std::string            for_find;
    std::string            for_replase;
    void                   first();
    void                   second();
    int                    testInputString();
    int                    getSum(std::string& sum);
    void                   intToStr(std::string &str, int& sum);

public:
                           ManagerThread();
    void                   startThreads();
};

#endif // MANAGER_THREAD_H
