//
// Created by funtik on 14.05.19.
//

#include "gtest/gtest.h"
#include "../client.h"

std::vector<char *> createArgv(char* arg1, char* arg2 = nullptr, char* arg3 = nullptr){
    std::vector<char*> v = std::vector<char*>();
    v.push_back("test");
    v.push_back(arg1);
    if(arg2 != nullptr){
        v.push_back(arg2);
    }
    if(arg2 != nullptr){
        v.push_back(arg3);
    }
    return v;
}

TEST(InvalidArgument,zero_arguments){
    EXPECT_EQ("invalid argument count",client(0,nullptr));
}


TEST(InvalidArgument,more_then_3){
    EXPECT_EQ("invalid argument count",client(4,nullptr));
}


TEST(Connection,estiblishConnection){
    auto v = createArgv("os");
    EXPECT_EQ("super os",client(v.size(),&v[0]));
}

int main(int argc, char *argv[]) {
//    auto v = createArgv("os");
//    std::cout << client(4,&v[0]);
//    return 0;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}