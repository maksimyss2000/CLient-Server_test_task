#include "manager_thread.h"


ManagerThread::ManagerThread(int argc, char *argv[]){
    for_find    = "02468";
    for_replase = "KB";
    client      = std::make_unique<Client>(argc, argv);
    queue       = std::make_unique<Semafore>(0);
}


int ManagerThread::testInputString(){
    std::size_t found = input.find_first_not_of("0123456789");
    if (input.length() > 64 || found != std::string::npos) {
        /* dbg */
        //std::cout << "DBG: not push str:" << input << std::endl;
        return 1;
    }

    std::sort(input.begin(), input.end());
    /* dbg */
    //std::cout << "DBG sort str:" << input << std::endl;

    while ((found = input.find_first_of(for_find)) != std::string::npos) {
            input.replace(found, 1, for_replase);
    }
    /* @dbg */
    //std::cout << "DBG replase str:" << input << std::endl;
    return 0;
}


int ManagerThread::getSum(std::string& str){
    int sum = 0;
    for (char &simbol :  str) {
        if (isdigit(simbol)) {
            sum += simbol - '0';
        }
    }
    std::cout << "The sum digits of the line \'" << str << "\' = " << sum << std::endl;
    return sum;
}


void ManagerThread::intToStr(std::string& str, int& sum){
    std::stringstream ss;
    ss << sum;
    str = ss.str();
}


/* The solution comes down to the typical consumer-producer problem with a circle buffer.
 * The problem specifies only 2 threads, but works for more.
 */
void ManagerThread::first(){
    while (true) {                         /* start main producer logic */
        std::getline(std::cin, input);
        if (testInputString()) {
            continue;;
        }
        mutex.lock();
        buffer.push(input);
        mutex.unlock();

        queue->up();
    }
}


void ManagerThread::second(){
    int sum;
    std::string str;
    while (true) {                         /* start main consumer logic */
        queue->down();
        mutex.lock();

        str = buffer.front();
        buffer.pop();

        mutex.unlock();

        sum = getSum(str);
        intToStr(str, sum);
        client->sendMessage(str);
    }
}


void ManagerThread::startThreads(){
    std::thread first_th(&ManagerThread::first, this);
    std::thread second_th(&ManagerThread::second, this);
    first_th.join();
    second_th.join();
}
