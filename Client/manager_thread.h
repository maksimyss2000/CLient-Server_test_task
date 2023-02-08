#ifndef MANAGER_THREAD_H
#define MANAGER_THREAD_H


#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <string>
#include <chrono>
#include <cstddef>
#include <fstream>
#include <cstdio>
#include <queue>
#include <memory>
#include <bits/stdc++.h>

#include "semafore.h"
#include "client.h"


class ManagerThread {
    std::unique_ptr<Client>   client;
    std::unique_ptr<Semafore> queue;
    std::mutex                mutex;
    std::queue<std::string>   buffer; 
    std::string               input;
    std::string               for_find;
    std::string               for_replase;

    void                      first();
    void                      second();
    int                       testInputString();
    int                       getSum(std::string& str);
    void                      intToStr(std::string& str, int& sum);

public:
                              ManagerThread(int argc, char *argv[]);
    void                      startThreads();
};

#endif // MANAGER_THREAD_H
