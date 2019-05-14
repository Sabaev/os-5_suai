cmake_minimum_required(VERSION 3.9)
project(lab5_fake_server)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab5_fake_server main.cpp ../common/UDPSocket.h ../common/UDPSocket_fake_server.h)


target_link_libraries(lab5_fake_server)