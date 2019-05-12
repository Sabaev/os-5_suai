# Отладка клиент-серверного взаимодействия
---
## Серверная часть (Windows)
### Сборка через CMake
    cmake_minimum_required(VERSION 3.9)
    project(lab4_windows_server)
    
    set(CMAKE_CXX_STANDARD 14)
    
    add_executable(lab4_windows_server main.cpp ../common/WSAsession.h ../common/UDPSocket.h)
    
    
    target_link_libraries(lab4_windows_server wsock32 ws2_32 stdc++fs)


### Вывод программы после запуска
    C:\Users\User\CLionProjects\osLab_4\server\cmake-build-debug\lab4_windows_server.exe
    SO_REUSEADDR Value: 0
    Set SO_REUSEADDR: ON
    SO_REUSEADDR Value: 1

---
## Клиентская часть (Linux)
### Сборка
    g++ -Wall -O3 main.cpp

### Запуск клиента на virtual box

    ./main os

### Вывод программы после запуска
    10

---
## Ручное тестирование
### Клиент
#####получение версии ос

	send: success
	10
    
#####получение списка файлов в директории
    
    ./main ls /
    send: success
    "/bin"
    "/cydrive"
    ...

#####получение информации о количесве файлов в директории
    
    ./main count /
    send: success
    14

### Сервер

	Received data from client with ip 192.168.1.15
    received command is: "count /"
    result of execution is: 14
    ===end working with client===
    
    ===wait for command from client===
    Received data from client with ip 192.168.1.15
    received command is: "os"
    result of execution is: 10
    ===end working with client===
    
    ===wait for command from client===
    Received data from client with ip 192.168.1.15
    received command is: "ls /"
    result of execution is: "/bin"
    "/cygdrive"
    "/Cygwin-Terminal.ico"
    "/Cygwin.bat"
    "/Cygwin.ico"
    "/dev"
    "/etc"
    "/home"
    "/lib"
    "/sbin"
    "/tmp"
    "/usr"
    "/var"
    "/proc"
    
    ===end working with client===
    
    ===wait for command from client===
    Received data from client with ip 192.168.1.6
    received command is: "os"
    result of execution is: 10
    ===end working with client===
    
    ===wait for command from client===
    Received data from client with ip 192.168.1.15
    received command is: "os"
    result of execution is: 10
    ===end working with client===
    