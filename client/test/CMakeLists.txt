cmake_minimum_required(VERSION 3.9)
project(test)

add_subdirectory(googletest)

include_directories(${GTEST_SOURCE_DIR}/include ${GTEST_SOURCE_DIR})


add_executable(runTests main.cpp ../client.h)

target_link_libraries(runTests gtest gtest_main)
target_link_libraries(runTests pthread)