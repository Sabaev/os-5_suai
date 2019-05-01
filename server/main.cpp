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
    const char* SERVER_IP = "192.168.56.1";

    try {
        WSASession Session;
        UDPSocket Socket;
        char buffer[bufSize];

        Socket.Bind(port, SERVER_IP);
        while (true) {
            sockaddr_in add = Socket.RecvFrom(buffer, sizeof(buffer));
            std::string input(buffer);
            std::cerr << buffer << std::endl;
            std::string res = doAction(input);
            std::cout << res << std::endl;
            Socket.SendTo(add, res.c_str(), res.size());
        }
    }
    catch (std::system_error &e) {
        std::cout << e.what();
    }

    return 0;
}
