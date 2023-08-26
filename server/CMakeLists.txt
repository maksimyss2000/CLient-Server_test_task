cmake_minimum_required(VERSION 2.6)

project(server)

set(SRC_DIR src)
set(SOURCES ${SRC_DIR}/main.cpp  ${SRC_DIR}/server.cpp)

add_executable(server.out ${SOURCES})

target_link_libraries(server.out mhash)