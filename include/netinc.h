#ifndef NETINC_H
#define NETINC_H

#include <stdio.h>
#include <string.h>

#ifdef _WIN32

#include <Winsock2.h>
#include <WS2tcpip.h>

#define WinsockStartup \
    WSADATA wsa;\
    WSAStartup(MAKEWORD(2,2), &wsa);
#define WinsockCleanup WSACleanup();

#else

#define closesocket close
#define WinsockStartup ;
#define WinsockCleanup ;

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#endif

#endif