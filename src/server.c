#include "server.h"

void server() {
    // create socket
    const int fd = socket(PF_INET, SOCK_STREAM, 0);

    // bind to open port
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(49999);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(fd, (struct sockaddr*) &addr, sizeof(addr))) {
        perror("bind error:");
        return;
    }

    // read port
    socklen_t addr_len = sizeof(addr);
    getsockname(fd, (struct sockaddr*) &addr, &addr_len);
    printf("server is on port %d\n", (int) ntohs(addr.sin_port));
    if (listen(fd, 1)) {
        perror("listen error:");
        return;
    }

    // accept incoming connection
    struct sockaddr_storage caddr;
    socklen_t caddr_len = sizeof(caddr);
    const int cfd = accept( fd, (struct sockaddr*) &caddr, &caddr_len );


    // read from client
    char buf[1024];
    recv( cfd, buf, sizeof(buf), 0 );
    printf("client says:\n    %s\n", buf );
    closesocket(cfd);

    closesocket(fd);
}