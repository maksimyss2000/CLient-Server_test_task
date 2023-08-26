#include "manager_threads.h"
#include "handle_str.h"

ManagerThread::ManagerThread() {
    work_status = working;
}

void ManagerThread::setStrInBuffer(std::string& str) {
    std::lock_guard<std::mutex> lock(buffer_mutex);

    buffer.push(str);
}

std::string ManagerThread::getStrByBuffer() {
    std::lock_guard<std::mutex> lock(buffer_mutex);

    std::string str = buffer.front();
    buffer.pop();
    return str;
}

void ManagerThread::getStrByConsole() {
    std::string input_str;
    while (work_status == working) {                         /* start main producer logic */
        std::getline(std::cin, input_str);

        if (!testInputStr(input_str)) {
            continue;
        }

        std::sort(input_str.begin(), input_str.end());
        replaceAllEven(input_str);

        setStrInBuffer(input_str);
        semafore.release();
    }
}

void ManagerThread::sendStrByClient() {
    int sum;
    std::string str;
    while (work_status == working) {                         /* start main consumer logic */
        semafore.acquire();
        str = getStrByBuffer();

        std::cout << "thread#2: received str = " << str << std::endl;
        sum = calculateSumStr(str);

        client.sendInteger(sum);
    }
}

/* typical produser-consumer solution */
void ManagerThread::startThreads() {
    std::thread first_th(&ManagerThread::getStrByConsole, this);
    std::thread second_th(&ManagerThread::sendStrByClient, this);
    first_th.join();
    second_th.join();
}
