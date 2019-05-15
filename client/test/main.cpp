//
// Created by funtik on 14.05.19.
//

#include <cstdarg>
#include "gtest/gtest.h"
#include "../client.h"



std::vector<std::string> createArgv(const std::string &arg1, const char *arg2 = nullptr,const char *arg3 = nullptr){
    std::vector<std::string> v;
    v.emplace_back("test");
    v.emplace_back(arg1);
    if(arg2 != nullptr){
        v.emplace_back(arg2);
    }
    if(arg3 != nullptr){
        v.emplace_back(arg3);
    }

    return v;
}

TEST(InvalidArgument,zero_arguments){
    EXPECT_EQ("invalid argument count",client(0,std::vector<std::string>()));
}


TEST(InvalidArgument,more_then_3){
    EXPECT_EQ("invalid argument count",client(4,std::vector<std::string>()));
}


TEST(Connection,estiblishConnection){
    std::vector<std::string> v = createArgv("os");
    EXPECT_EQ("super os",client(v.size(),v));
}

int main(int argc,char *argv[]) {
//    auto v = createArgv("os");
//    std::cout << client(argc,argv);
//    return 0;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}