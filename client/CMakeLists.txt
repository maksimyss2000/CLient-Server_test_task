cmake_minimum_required(VERSION 2.6)

project(client)

set(SRC_DIR src)
set(SOURCES ${SRC_DIR}/client.cpp  ${SRC_DIR}/handle_str.cpp ${SRC_DIR}/main.cpp ${SRC_DIR}/manager_threads.cpp  ${SRC_DIR}/semafore.cpp)

add_executable(client.out ${SOURCES})

