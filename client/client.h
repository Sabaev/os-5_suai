//
// Created by funtik on 14.05.19.
//

#ifndef LAB4_CLIENT_LINUX_CLIENT_H
#define LAB4_CLIENT_LINUX_CLIENT_H

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>

static const int MAX_DATA_SIZE = 512;
static const std::string count = "count";
static std::string ls = "ls";
static std::string os = "os";
static const int server_port = 8080;
static const std::string server_ip  = "127.0.0.1";

const std::string checkInput(int argc, char *argv[]) {
    if (argc == 3) {
        if (strncmp(argv[1], ls.c_str(), ls.size()) != 0 && strncmp(argv[1], count.c_str(), count.size()) != 0) {
            return  "invalid command";

        }
    } else if (argc == 2) {
        if (strncmp(argv[1], os.c_str(), os.size()) != 0) {
            return "invalid command";
        }
    } else {
        return "invalid argument count";
    }
    return "ok";
}
bool isValidDataSize(const std::string &data) {
    return data.size() < MAX_DATA_SIZE;
}
void sendCommand(const std::string &command, int sock,sockaddr_in serv_addr, const std::string &data = "") {
    if (command == os) {
        sendto(sock, os.c_str(), os.size(), 0,(struct sockaddr *)&serv_addr, sizeof(serv_addr));
    } else {
        if (isValidDataSize(data)) {
            std::string tmp = (command + " " + data);
            sendto(sock, tmp.c_str(), tmp.size(), 0,(struct sockaddr *)&serv_addr, sizeof(serv_addr));
        } else {
            std::cerr << "too big data, must be smaller than: " + std::to_string(MAX_DATA_SIZE);
            exit(EXIT_FAILURE);
        }
    }
}

std::string client(int argc, char **argv){
    char buf[MAX_DATA_SIZE + 1];
    int sock;
    struct sockaddr_in serv_addr{};
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    std::string inputCheck = checkInput(argc, argv);
    if(inputCheck != "ok"){
        return inputCheck;
    }
    if (sock < 0) {
        perror("socket");
        exit(1);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(server_port);
    serv_addr.sin_addr.s_addr = inet_addr(server_ip.c_str());

    if (argc == 2) {
        sendCommand(argv[1], sock, serv_addr);
    } else {
        sendCommand(argv[1], sock,serv_addr, argv[2]);
    }

    perror("send");
    int recsize = recv(sock, buf, sizeof(buf), 0);
    buf[recsize] = '\0';
    close(sock);
    return buf;
}

#endif //LAB4_CLIENT_LINUX_CLIENT_H
