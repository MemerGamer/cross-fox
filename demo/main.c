#include <stdio.h>
#include  <string.h>
#include "../fox/headers/models/networking/server.h"

//ideas
// fox_settings settings = calloc(1, sizeof(fox_settings));
// settings->port = "8080";
/**
 * settings:
 *  - port: alapbol NULL
 */
// fox_add_endpoint("/app/get/", FOX_GET, &myFunc);
// fox_start_server(settings);

void fox_launch(struct FoxServer *server){

    char buffer[30000];
    char *hello = "HTTP/1.1 200 OK\nGMT\nServer: Apache/2.2.14 (Win32)\nLast-Modified: Wed, 22 Jul 2009 19:15:56 GMT\nContent-Type: text/html\nConnection: Closed\n\n<html><body><h1>Hello, Fox</h1></body></html>";

    int address_length = sizeof(server->address);
    int new_socket = accept(server->socket, (struct  sockaddr*)&server->address, (int*)&address_length);

    while(1){
        printf("====== Waiting for connection ======");
        recv(new_socket,buffer,30000,0);
        printf("%s\n",buffer);
        send(new_socket, hello, strlen(hello), 0 );
        closesocket(new_socket);
    }

}

int main() {
    printf("Hello, Cross-Fox App\n");

    struct FoxServer server = fox_server_constructor(AF_INET,SOCK_STREAM, 0 ,INADDR_ANY, 8080, 10, fox_launch);
    server.fox_launch(&server);


    return 0;
}
