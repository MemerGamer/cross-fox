//
// Created by kovacs on 2022. 04. 14..
//

#ifndef CROSS_FOX_SERVER_H
#define CROSS_FOX_SERVER_H

#include <WinSock2.h>

//for Unix systems
//#include <sys/socket.h>
//#include <netinet/in.h>

typedef struct{
    int domain;
    int service;
    int protocol;
    u_long _interface;
    int port;
    int backlog;

    struct sockaddr_in address;

    int socket;

    void (*launch)(void);
}FoxServer;

FoxServer fox_server_constructor(int domain, int service, int protocol, u_long _interface, int port, int backlog,void(*launch)(void));


#endif //CROSS_FOX_SERVER_H
