//
// Created by User on 4/21/2019.
//

#ifndef LAB4_WINDOWS_WSASESSION_H
#define LAB4_WINDOWS_WSASESSION_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <system_error>
#include <string>
#include <iostream>

class WSASession
{
public:
    WSASession()
    {
        int ret = WSAStartup(MAKEWORD(2, 2), &data);
        if (ret != 0)
            throw std::system_error(WSAGetLastError(), std::system_category(), "WSAStartup Failed");

    }
    ~WSASession()
    {
        WSACleanup();
    }
private:
    WSAData data{};
};


#endif //LAB4_WINDOWS_WSASESSION_H
