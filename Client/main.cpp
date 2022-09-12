#include <iostream>
#include <signal.h>
#include "manager_thread.h"
#include <string>


int main(){
    ManagerThread manager;
    manager.startThreads();
    return 0;
}
