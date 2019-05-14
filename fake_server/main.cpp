//
// Created by User on 4/21/2019.
//

#include <stdio.h>
#include "../common/UDPSocket_fake_server.h"
#include <wchar.h>
#include <sstream>
#include <sys/utsname.h>
#include <netinet/in.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

const std::string osVersion() {
    utsname buf{};
    uname(&buf);
    return buf.version;
}

const std::string doAction(const std::string &command) {
    int delPos = command.find(' ');
    std::string action = command.substr(0, delPos);
    std::string arg = command.substr(delPos + 1, command.size() - 1);

    if (action == "ls") {
        return "some dir";
    } else if (action == "count") {
        return "100";
    } else if (command == "os") {
        return "super os";
    } else {
        return "error command not found";
    }
}

// todo make start with parameters only for linux
// todo install virtual box
int main() {
    const int port = 8080;
    const int bufSize = 513;
    const char* SERVER_IP = "127.0.0.1";

    try {
        UDPSocket Socket;
        char commandBuffer[bufSize];

        Socket.Bind(port, SERVER_IP);
        while (true) {
            std::cerr << "=== wait for command from client ===" << std::endl;
            sockaddr_in add = Socket.RecvFrom(commandBuffer, sizeof(commandBuffer));

            // take client
            char* clientIp = inet_ntoa(add.sin_addr);
            std::cerr << "Received data from client with ip " << clientIp << std::endl;

            // load commandBuffer
            std::string input(commandBuffer);
            std::cerr << "received command is: \"" << commandBuffer << "\"" << std::endl;

            // try to execute command
            std::string res = doAction(input);
            std::cerr << "result of execution is: " <<res << std::endl;

            std::cerr << "answer's size is "<< res.size() << std::endl;
            // send result to client
            Socket.sendToClient(add, res.c_str(), res.size());

            std::cerr << "*** end working with client ***" << std::endl << std::endl;
        }
    }
    catch (std::system_error &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

#pragma clang diagnostic pop