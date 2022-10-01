#ifndef MANAGER_THREAD_H
#define MANAGER_THREAD_H


#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <string>
#include <list>
#include <chrono>
#include <bits/stdc++.h>
#include <cstddef>
#include <fstream>
#include <cstdio>

#include "semafore.h"
#include "client.h"

#define  SIZE_BUFER     5
#define  NAMEDPIPE_NAME "./myFile.txt"

class ManagerThread {
    int                    fd;
    Client                 client;
    std::mutex             mutex;
    Semafore*              queue;
    std::string            input;
    std::string            for_find;
    std::string            for_replase;
    std::ofstream          myFile_input;
    std::ifstream          myFile_output;

    void                   first();
    void                   second();
    int                    testInputString();
    int                    getSum(std::string& str);
    void                   intToStr(std::string& str, int& sum);

public:
                           ManagerThread();
                           ~ManagerThread();
    void                   startThreads();
};

#endif // MANAGER_THREAD_H
