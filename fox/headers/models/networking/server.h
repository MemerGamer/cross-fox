//
// Created by kovacs on 2022. 04. 14..
//

#ifndef CROSS_FOX_SERVER_H
#define CROSS_FOX_SERVER_H

#include <WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")

//for Unix systems:
//  #include <sys/socket.h>
//  #include <netinet/in.h>

struct FoxServer{
    int domain;
    int service;
    int protocol;
    u_long _interface;
    int port;
    int backlog;

    struct sockaddr_in address;

    unsigned int socket;

    void (*fox_launch)(struct FoxServer *server);
};

//this is the declaration of the constructor
struct FoxServer fox_server_constructor(int domain, int service, int protocol, u_long _interface, int port, int backlog,void(*fox_launch)(struct FoxServer *server));


#endif //CROSS_FOX_SERVER_H
