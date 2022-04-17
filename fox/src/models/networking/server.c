//
// Created by kovacs on 2022. 04. 14..
//

#include "../../../headers/models/networking/server.h"
#include <stdio.h>
#include <stdlib.h>

//this is the implementation of the constructor, this function initializes the constructor with input data
struct FoxServer fox_server_constructor(int domain, int service, int protocol, u_long _interface, int port, int backlog,
                                        void (*fox_launch)(struct FoxServer *server)) {
    struct FoxServer server;
    server.domain = domain;
    server.service = service;
    server.protocol = protocol;
    server._interface = _interface;
    server.port = port;
    server.backlog = backlog;

    server.address.sin_family = domain;
    server.address.sin_port = htons(port);
    server.address.sin_addr.s_addr = htonl(_interface);

    server.socket = socket(domain,service,protocol);

    //check if the socket is open
    if(server.socket == 0){
        perror("Failed to connect socket...\n");
        exit(1);
    }

    if(bind(server.socket, (struct sockaddr*)&server.address,sizeof(server.address)) < 0){
        perror("Failed to bind socket...\n");
        exit(1);
    }

    if(listen(server.socket,server.backlog) < 0){
        perror("Failed to start listening...\n");
        exit(1);
    }

    server.fox_launch = fox_launch;

    return server;
}
