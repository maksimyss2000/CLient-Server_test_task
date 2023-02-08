#include <iostream>
#include <string>
#include <signal.h>
#include "manager_thread.h"


int main(){
    ManagerThread manager;
    manager.startThreads();
    return 0;
}
