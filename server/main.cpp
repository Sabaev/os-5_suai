//
// Created by User on 4/21/2019.
//

#include <winsock2.h>
#include <stdio.h>
#include "../common/WSAsession.h"
#include "../common/UDPSocket.h"
#include <wchar.h>
#include <sstream>
#include <experimental/filesystem>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
namespace fs = std::experimental::filesystem;

const std::string listDir(const fs::path &path) {
    if (fs::is_directory(path)) {
        std::stringstream stringstream;
        for (const auto &entry : fs::directory_iterator(path)) {
            stringstream << entry.path() << std::endl;
        }
        return stringstream.str();
    } else {
        return "no dir";
    }
}

const int countDir(const fs::path &path) {
    return std::distance(fs::directory_iterator(path), fs::directory_iterator());
}

const int osVersion() {
    OSVERSIONINFO osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&osvi);
    return osvi.dwMajorVersion;
}

const std::string doAction(const std::string &command) {
    int delPos = command.find(' ');
    std::string action = command.substr(0, delPos);
    std::string arg = command.substr(delPos + 1, command.size() - 1);

    if (action == "ls") {
        return listDir(arg);
    } else if (action == "count") {
        return std::to_string(countDir(arg));
    } else if (command == "os") {
        return std::to_string(osVersion());
    } else {
        return "error command not found";
    }
}

// todo make start with parameters only for linux
// todo install virtual box
int main() {
    const int port = 8080;
    const int bufSize = 513;
    const char* SERVER_IP = "192.168.1.9";

    try {
        WSASession Session;
        UDPSocket Socket;
        char commandBuffer[bufSize];

        Socket.Bind(port, SERVER_IP);
        while (true) {
            std::cout << "=== wait for command from client ===" << std::endl;
            sockaddr_in add = Socket.RecvFrom(commandBuffer, sizeof(commandBuffer));

            // take client
            char* clientIp = inet_ntoa(add.sin_addr);
            std::cout << "Received data from client with ip " << clientIp << std::endl;

            // load commandBuffer
            std::string input(commandBuffer);
            std::cout << "received command is: \"" << commandBuffer << "\"" << std::endl;

            // try to execute command
            std::string res = doAction(input);
            std::cout << "result of execution is: " <<res << std::endl;

            // send result to client
            Socket.SendTo(add, res.c_str(), res.size());

            std::cout << "*** end working with client ***" << std::endl << std::endl;
        }
    }
    catch (std::system_error &e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}

#pragma clang diagnostic pop