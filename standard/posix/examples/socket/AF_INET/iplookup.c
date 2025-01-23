#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>
#include <netdb.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usages: %s <HOST> [PORT]\n", argv[0]);
        return 1;
    }

    if (argv[1][0] == '\0') {
        fprintf(stderr, "usages: %s <HOST> [PORT], <HOST> should be non-empty.\n", argv[0]);
        return 1;
    }

    const char * host = argv[1];
    const char * port = argv[2];

    if (port == NULL || port[0] == '\0') {
        port = "80";
    }

    //////////////////////////////////////////////////////////////

    struct addrinfo hints = { .ai_family = AF_UNSPEC, .ai_socktype = SOCK_STREAM };
    struct addrinfo *result;

    int ret = getaddrinfo(host, port, &hints, &result);

    if (ret != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ret));
        return 1;
    }

    //////////////////////////////////////////////////////////////

    char s[INET6_ADDRSTRLEN + 1];

    for (struct addrinfo * p = result; p != NULL; p = p->ai_next) {
        switch(p->ai_addr->sa_family) {
            case AF_INET:
                memset(s, 0, sizeof(s));

                if (inet_ntop(AF_INET, &(((struct sockaddr_in *)p->ai_addr)->sin_addr), s, INET_ADDRSTRLEN) == NULL) {
                    perror(NULL);
                    freeaddrinfo(result);
                    return 2;
                }

                puts(s);
                break;
            case AF_INET6:
                memset(s, 0, sizeof(s));

                if (inet_ntop(AF_INET6, &(((struct sockaddr_in6 *)p->ai_addr)->sin6_addr), s, INET6_ADDRSTRLEN) == NULL) {
                    perror(NULL);
                    freeaddrinfo(result);
                    return 2;
                }

                puts(s);
                break;
        }
    }

    freeaddrinfo(result);
    return 0;
}
