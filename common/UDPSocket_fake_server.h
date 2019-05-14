//
// Created by funtik on 12.05.19.
//

#ifndef LAB5_FAKE_SERVER_UDPSOCKET_FAKE_SERVER_H
#define LAB5_FAKE_SERVER_UDPSOCKET_FAKE_SERVER_H

//
// Created by User on 4/21/2019.
//

#ifndef LAB4_WINDOWS_SOCKET_H

#include <system_error>
#include <string>
#include <iostream>
#include <netinet/in.h>
#include <zconf.h>
#include <arpa/inet.h>
#include <cstring>

class UDPSocket {
public:
    UDPSocket() {
        sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (sock < 0)
            throw std::system_error(1, std::system_category(), "Error opening socket");
        setSocketOptions();
    }

    ~UDPSocket() {
        close(sock);
    }


    sockaddr_in RecvFrom(char *buffer, int len, int flag = 0) {
        sockaddr_in from{};
        uint size = sizeof(from);
        int ret = recvfrom(sock, buffer, len, flag,(struct sockaddr *)&from,(socklen_t *)&size);
        if (ret < 0) {
            throw std::system_error(2, std::system_category(), "recv failed");
        }

        // make the buffer zero terminated
        buffer[ret] = 0;
        return from;
    }

    void sendToClient(const std::string &address, unsigned short port, const char *buffer, int len, int flags = 0) {
        sockaddr_in add{};
        add.sin_family = AF_INET;
        add.sin_addr.s_addr = inet_addr(address.c_str());
        add.sin_port = htons(port);
        uint addr_size = sizeof(add);
        int ret = sendto(sock, buffer, len, flags, reinterpret_cast<struct sockaddr *>(&add), reinterpret_cast<socklen_t >(addr_size));
        if (ret < 0)
            throw std::system_error(5, std::system_category(), "sendto failed");
    }

    void sendToClient(sockaddr_in &address, const char *buffer, int len, int flags = 0) {
        uint addr_size = sizeof(address);
        int ret = sendto(sock, buffer, len, flags, reinterpret_cast<struct sockaddr *>(&address), reinterpret_cast<socklen_t >(addr_size));
        std::cerr << "ret is " << ret << std::endl;
        std::cerr << "buffer is " <<buffer << " buffer size is " << strlen(buffer);
        if (ret < 0)
            throw std::system_error(3, std::system_category(), "sendto failed");
    }

    void Bind(unsigned short port, const std::string &ip_add) {
        sockaddr_in add{};
        add.sin_family = AF_INET;
        add.sin_addr.s_addr = inet_addr(ip_add.c_str());
        add.sin_port = htons(port);
        uint addr_size = sizeof(add);

        int ret = bind(sock, reinterpret_cast<struct sockaddr *>(&add),reinterpret_cast<socklen_t >(addr_size));
        if (ret < 0)
            throw std::system_error(ret, std::system_category(), "Bind failed");
    }

private:
    void setSocketOptions() {
        int iResult = 0;
        bool bOptVal = true;
        int bOptLen = sizeof(bool);
        int iOptVal = 0;
        int iOptLen = sizeof(int);

        // set options for reusing
        iResult = getsockopt(sock,SOL_SOCKET,SO_REUSEADDR,(char *) &iOptVal,(socklen_t *) &iOptLen);
        if (iResult < 0) {
            wprintf(L"getsockopt for SO_REUSEADDR failed with error: %u\n", iResult);
        } else {
            wprintf(L"SO_REUSEADDR Value: %ld\n", iOptVal);
        }

        iResult = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *) &bOptVal, bOptLen);
        if (iResult < 0) {
            wprintf(L"setsockopt for SO_REUSEADDR failed with error: %u\n", iResult);
        } else {
            wprintf(L"Set SO_REUSEADDR: ON\n");
        }
        iResult = getsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *) &iOptVal,(socklen_t *) &iOptLen);
        if (iResult < 0) {
            wprintf(L"getsockopt for SO_REUSEADDR failed with error: %u\n", iResult);
        } else
            wprintf(L"SO_REUSEADDR Value: %ld\n", iOptVal);
    }

    int sock;
};


#endif //LAB4_WINDOWS_SOCKET_H


#endif //LAB5_FAKE_SERVER_UDPSOCKET_FAKE_SERVER_H
