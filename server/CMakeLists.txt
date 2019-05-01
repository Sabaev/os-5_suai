cmake_minimum_required(VERSION 3.9)
project(lab4_windows_server)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab4_windows_server main.cpp ../common/WSAsession.h ../common/UDPSocket.h)


target_link_libraries(lab4_windows_server wsock32 ws2_32 stdc++fs)