#include <vector>
#include "client.h"

int main(int argc, char *argv[]) {
    std::vector<std::string> argList(argv,argv + argc);
    std::cout << client(argList.size(),argList);
    return 0;
}
