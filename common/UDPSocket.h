//
// Created by User on 4/21/2019.
//

#ifndef LAB4_WINDOWS_SOCKET_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <system_error>
#include <string>
#include <iostream>

class UDPSocket {
public:
    UDPSocket() {
        sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (sock == INVALID_SOCKET)
            throw std::system_error(WSAGetLastError(), std::system_category(), "Error opening socket");
        setSocketOptions();
    }

    ~UDPSocket() {
        closesocket(sock);
    }


    sockaddr_in RecvFrom(char *buffer, int len, int flags = 0) {
        sockaddr_in from{};
        int size = sizeof(from);
        int ret = recvfrom(sock, buffer, len, flags,reinterpret_cast<SOCKADDR *>(&from), &size);
        if (ret < 0) {
            throw std::system_error(WSAGetLastError(), std::system_category(), "recvfrom failed");
        }

        // make the buffer zero terminated
        buffer[ret] = 0;
        return from;
    }

    void SendTo(const std::string& address, unsigned short port, const char* buffer, int len, int flags = 0)
    {
        sockaddr_in add;
        add.sin_family = AF_INET;
        add.sin_addr.s_addr = inet_addr(address.c_str());
        add.sin_port = htons(port);
        int ret = sendto(sock, buffer, len, flags, reinterpret_cast<SOCKADDR *>(&add), sizeof(add));
        if (ret < 0)
            throw std::system_error(WSAGetLastError(), std::system_category(), "sendto failed");
    }
    void SendTo(sockaddr_in& address, const char* buffer, int len, int flags = 0)
    {
        int ret = sendto(sock, buffer, len, flags, reinterpret_cast<SOCKADDR *>(&address), sizeof(address));
        if (ret < 0)
            throw std::system_error(WSAGetLastError(), std::system_category(), "sendto failed");
    }

    void Bind(unsigned short port, const std::string &ip_add ) {
        sockaddr_in add{};
        add.sin_family = AF_INET;
        add.sin_addr.s_addr = inet_addr(ip_add.c_str());
        add.sin_port = htons(port);

        int ret = bind(sock, reinterpret_cast<SOCKADDR *>(&add), sizeof(add));
        if (ret < 0)
            throw std::system_error(WSAGetLastError(), std::system_category(), "Bind failed");
    }

private:
    void setSocketOptions() {
        int iResult = 0;
        BOOL bOptVal = TRUE;
        int bOptLen = sizeof(BOOL);
        int iOptVal = 0;
        int iOptLen = sizeof(int);

        // set options for reusing
        iResult = getsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *) &iOptVal, &iOptLen);
        if (iResult == SOCKET_ERROR) {
            wprintf(L"getsockopt for SO_REUSEADDR failed with error: %u\n", WSAGetLastError());
        } else
            wprintf(L"SO_REUSEADDR Value: %ld\n", iOptVal);

        iResult = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *) &bOptVal, bOptLen);
        if (iResult == SOCKET_ERROR) {
            wprintf(L"setsockopt for SO_REUSEADDR failed with error: %u\n", WSAGetLastError());
        } else
            wprintf(L"Set SO_REUSEADDR: ON\n");

        iResult = getsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *) &iOptVal, &iOptLen);
        if (iResult == SOCKET_ERROR) {
            wprintf(L"getsockopt for SO_REUSEADDR failed with error: %u\n", WSAGetLastError());
        } else
            wprintf(L"SO_REUSEADDR Value: %ld\n", iOptVal);
    }

    SOCKET sock;
};


#endif //LAB4_WINDOWS_SOCKET_H
