//#include <pthread.h>
#include <stdio.h>
#include <string.h>

#include "server.h"
#include "client.h"

int main(int argc, char *argv[]) {

    WinsockStartup;

    if (argc > 1 && !strcmp(argv[1], "client")) {
        if (argc != 3) {
            fprintf(stderr, "not enough args!");
            return -1;
        }

        int port;
        sscanf(argv[2], "%d", &port);

        client( "localhost", port );
    } else {
        server();
    }

    WinsockCleanup;

    return 0;
}
