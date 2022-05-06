#include <stdio.h>
#include <string.h>
#include "server.h"
#include  <signal.h>

//ideas
// fox_settings settings = calloc(1, sizeof(fox_settings));
// settings->port = "8080";
/**
 * settings:
 *  - port: alapbol NULL
 */
// fox_add_endpoint("/app/get/", FOX_GET, &myFunc);
// fox_start_server(settings);

void  INThandler(int sig){
    char  c;

    signal(sig, SIG_IGN);
    printf("Do you really want to quit? [y/n] ");
    c = getchar();
    if (c == 'y' || c == 'Y'){
        WSACleanup();
        exit(0);
    }
    else{
        signal(SIGINT, INThandler);
    }
    getchar(); // Get new line character
}


void fox_launch_old(struct FoxServer *server){

    char buffer[30000];
    char *hello = "HTTP/1.1 200 OK\nGMT\nServer: Apache/2.2.14 (Win32)\nLast-Modified: Wed, 22 Jul 2009 19:15:56 GMT\nContent-Type: text/html\nConnection: Closed\n\n<html><body><h1>Hello, Fox</h1></body></html>";

    int address_length = sizeof(server->address);
    unsigned int new_socket = accept(server->socket, (struct  sockaddr*)&server->address, (int*)&address_length);

    while(1){
        printf("====== Waiting for connection ======");
        recv(new_socket,buffer,30000,0);
        printf("%s\n",buffer);
        send(new_socket, hello, (int)strlen(hello), 0 );
        closesocket(new_socket);
    }

}

int fox_launch_new(){
    // Initialize Winsock.
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR) {
        wprintf(L"WSAStartup failed with error: %ld\n", iResult);
        return 1;
    }
    //----------------------
    // Create a SOCKET for listening for
    // incoming connection requests.
    SOCKET ListenSocket;
    ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ListenSocket == INVALID_SOCKET) {
        wprintf(L"socket failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    //----------------------
    // The sockaddr_in structure specifies the address family,
    // IP address, and port for the socket that is being bound.
    struct sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr("127.0.0.1");
    service.sin_port = htons(80);

    if (bind(ListenSocket,
             (SOCKADDR *) & service, sizeof (service)) == SOCKET_ERROR) {
        wprintf(L"bind failed with error: %ld\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }
    //----------------------
    // Listen for incoming connection requests.
    // on the created socket
    if (listen(ListenSocket, 1) == SOCKET_ERROR) {
        wprintf(L"listen failed with error: %ld\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    int numberOfConnections = 1;

    signal(SIGINT, INThandler);
    while(1){
        //----------------------
        // Create a SOCKET for accepting incoming requests.
        SOCKET AcceptSocket;
        wprintf(L"Waiting for client to connect...\n");

        //----------------------
        // Accept the connection.
        AcceptSocket = accept(ListenSocket, NULL, NULL);
        if (AcceptSocket == INVALID_SOCKET) {
            wprintf(L"accept failed with error: %ld\n", WSAGetLastError());
            closesocket(ListenSocket);
            WSACleanup();
            return 1;
        } else{
            wprintf(L"Client connected.\n");
            char buffer[30001];
            recv(AcceptSocket,buffer,30000,0);
            char hello[3000];
            //todo: response struct - strings
            sprintf(hello,"HTTP/1.1 200 OK GMT\nServer: Apache/2.2.14 (Win32)\nLast-Modified: Wed, 22 Jul 2009 19:15:56 GMT\nContent-Type: text/html\nConnection: Closed\n\n<html><body><h1>Hello, Fox %i!</h1></body></html>", numberOfConnections++);
            printf("\nSending:\n%s\n", hello);
            send(AcceptSocket, hello, (int)strlen(hello), 0 );
        }

        closesocket(AcceptSocket);
    }
}


int main() {
    fox_launch_new();
}
