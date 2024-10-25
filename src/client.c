#include "client.h"

void client( const char* ip, int port ) {
    const int fd = socket(PF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr = { 0 };
    addr.sin_family = AF_INET;
    addr.sin_port = htons((short) port);

    // connect to local machine at specified port

    char addrstr[NI_MAXHOST + NI_MAXSERV + 1];

    struct addrinfo hints;
    struct addrinfo *servinfo;

    memset(&hints, 0, sizeof hints); // make sure the struct is empty
    hints.ai_family = AF_INET;     // IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP stream sockets


	// remote.grayitsolutions.com
    getaddrinfo( ip, "49999", &hints, &servinfo );
    struct sockaddr_in *ipv4 = (struct sockaddr_in *)servinfo->ai_addr;
    void *TEST = &(ipv4->sin_addr);
    char ipstr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, TEST, ipstr, sizeof(ipstr));
    //char ipstr[] = "192.168.1.21";
    snprintf(addrstr, sizeof(addrstr), "%s:%d", ipstr, port);
    printf("attempting to connect to : %s\n", addrstr );

    // parse into address
    inet_pton(AF_INET, addrstr, &addr.sin_addr);

    // connect to server
    if (connect(fd, (struct sockaddr*) &addr, sizeof(addr))) {
        perror("connect error:");
        return;
    }

    // say hey with send!

    const char *msg = "the client says hello!";
    int iserror = send(fd, msg, strlen(msg) + 1, 0);
    printf("bytes = %d\n", iserror );
    closesocket(fd);
}
