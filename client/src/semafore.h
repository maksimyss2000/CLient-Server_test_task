#pragma once 

#include <mutex>
#include <condition_variable>

/// @brief classical semaphore implementation 
/// @details Semaphore is implemented as weak (waiting processes is a set) */
class Semafore {
private:
    int count;
    std::mutex mutex;
    std::condition_variable cond_var;
    
public:
    ///@brief
    ///@param int starting init for semafore (max threads for critical section). Default value is one.
    Semafore( int count = 0 ); 

    ///@brief classical semafore  atomic operation(up).
    void release();
    
    ///@brief classical semafore atomic acquire(down)
    void acquire();
};