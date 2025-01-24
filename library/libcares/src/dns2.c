#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <ares.h>

static void callback(void * arg, int status, int timeouts, struct ares_addrinfo * result) {
    printf("Result: %s, timeouts: %d\n", ares_strerror(status), timeouts);

    if (result != NULL) {
        struct ares_addrinfo_node * node;

        for (node = result->nodes; node != NULL; node = node->ai_next) {
            char        addr_buf[64] = "";
            const void *ptr          = NULL;

            if (node->ai_family == AF_INET) {
                const struct sockaddr_in *in_addr = (const struct sockaddr_in *)((void *)node->ai_addr);
                ptr = &in_addr->sin_addr;
            } else if (node->ai_family == AF_INET6) {
                const struct sockaddr_in6 *in_addr = (const struct sockaddr_in6 *)((void *)node->ai_addr);
                ptr = &in_addr->sin6_addr;
            } else {
                continue;
            }

            ares_inet_ntop(node->ai_family, ptr, addr_buf, sizeof(addr_buf));
            printf("%s\n", addr_buf);
        }

        ares_freeaddrinfo(result);
    }
}

int dns_lookup(const char * domain) {
    int ret = ares_library_init(ARES_LIB_INIT_ALL);

    if (ret != ARES_SUCCESS){
        fprintf(stderr, "%s\n", ares_strerror(ret));
        return ret;
    }

    ares_channel_t * channel = NULL;

    struct ares_options options;
    memset(&options, 0, sizeof(options));
    options.evsys = ARES_EVSYS_DEFAULT;

    ret = ares_init_options(&channel, &options, ARES_OPT_EVENT_THREAD);

    if (ret != ARES_SUCCESS) {
        fprintf(stderr, "%s\n", ares_strerror(ret));
        return ret;
    }

    ret = ares_set_servers_ports_csv(channel, "8.8.8.8");

    if (ret != ARES_SUCCESS) {
        fprintf(stderr, "%s\n", ares_strerror(ret));
        return ret;
    }

    struct ares_addrinfo_hints hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_flags  = ARES_AI_CANONNAME;

    ares_getaddrinfo(channel, domain, NULL, &hints, callback, NULL);

    ret = ares_queue_wait_empty(channel, -1);

    ares_destroy(channel);

    ares_library_cleanup();

    return ret;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <domain>", argv[0]);
        return 1;
    }

    return dns_lookup(argv[1]);
}
