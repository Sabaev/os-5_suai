cmake_minimum_required(VERSION 3.9)
project(lab4_client_linux)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab4_client_linux main.cpp ../common/UDPSocket.h client.h test/main.cpp)

target_link_libraries(lab4_client_linux std=c++14)