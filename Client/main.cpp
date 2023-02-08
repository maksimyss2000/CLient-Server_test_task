#include <iostream>
#include <string>
#include <signal.h>
#include "manager_thread.h"


int main(int argc, char *argv[]){
    ManagerThread manager(argc, argv);
    manager.startThreads();
    return 0;
}
