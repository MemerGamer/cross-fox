//
// Created by kovacs on 2022. 04. 14..
//

#include "../../../headers/models/networking/server.h"

FoxServer fox_server_constructor(int domain, int service, int protocol, u_long _interface, int port, int backlog,
                                        void (*launch)(void)) {
    FoxServer server;
    server.domain = domain;
    server.service = service;
    server.protocol = protocol;
    server._interface = _interface;
    server.port = port;
    server.backlog = backlog;

    server.address.sin_family = domain;
    server.address.sin_port = htons(port);
    server.address.sin_addr.s_addr = htonl(_interface);

    return server;
}
