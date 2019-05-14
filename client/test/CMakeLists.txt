project(test)

add_subdirectory(googletest)

include_directories(${googletest_SOURCE_DIR}/include ${googletest_SOURCE_DIR})


add_executable(runTests ../client.h)

target_link_libraries(runTests gtest gtest_main)
target_link_libraries(runTest)