#include "manager_thread.h"


ManagerThread::ManagerThread(){
    for_find    = "02468";
    for_replase = "KB";
}

int ManagerThread::testInputString(){
    std::size_t found = input.find_first_not_of("0123456789");
    if (input.length() > 64 || found != std::string::npos) {
        /* dbg */
        std::cout << "DBG: not push str:" << input << std::endl;
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
    for (char &simbol :str) {
        if (isdigit(simbol)) {
            sum += simbol - '0';
        }
    }
    std::cout << "The sum digits of the line \'" << str << "\' = " << sum << std::endl;
    return sum;
}


void ManagerThread::intToStr(std::string &str, int& sum){
    std::stringstream ss;
    ss << sum;
    str = ss.str();
}


/*The solution comes down to the typical consumer-producer problem with a bexoner buffer.
 *The buffer is a two-linked list for easy insertion at the beginning and removal from the end.
 * The problem specifies only 2 threads, but works for more.
 */


void ManagerThread::first(){
    while (true) {
        std::cin >> input;
        if (testInputString()) {
            continue;;
        }
        mutex.lock();                      /* start main producer logic */
        buf.push_back(input);
        mutex.unlock();
        semafore.up();
    }
}


void ManagerThread::second(){
    int sum;
    std::string* str;
    while (true) {
        semafore.down();                   /* start main consumer logic */
        mutex.lock();
        str = &buf.front();

        mutex.unlock();
        sum = getSum(*str);
        intToStr(*str, sum);
        client.sendMessage(*str);

        mutex.lock();
        buf.pop_front();
        mutex.unlock();
    }
}


void ManagerThread::startThreads(){
    std::thread first_th(&ManagerThread::first, this);
    std::thread second_th(&ManagerThread::second, this);
    first_th.join();
    second_th.join();
}
