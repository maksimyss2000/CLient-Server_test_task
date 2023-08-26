#pragma once 

#include <mutex>
#include <condition_variable>

/* Semaphore is implemented as weak (waiting processes is a set) */
class Semafore {
private:
    int count;
    std::mutex mutex;
    std::condition_variable cond_var;
    
public:
    Semafore(int count = 0);
    void release();
    void acquire();
};