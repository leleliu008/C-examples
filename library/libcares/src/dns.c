#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <ares.h>

static void state_cb(void * data, int s, int read, int write) {
    printf("Change state fd %d read:%d write:%d\n", s, read, write);
}


static void callback(void * arg, int status, int timeouts, struct hostent * host) {
    if(!host || status != ARES_SUCCESS){
        fprintf(stderr, "Failed to lookup %s\n", ares_strerror(status));
        return;
    }

    printf("Found address name %s\n", host->h_name);

    char ip[INET6_ADDRSTRLEN];

    for (int i = 0; host->h_addr_list[i]; ++i) {
        inet_ntop(host->h_addrtype, host->h_addr_list[i], ip, sizeof(ip));
        printf("%s\n", ip);
    }
}

static void wait_ares(ares_channel_t * channel) {
    for(;;){
        struct timeval *tvp, tv;
        fd_set read_fds, write_fds;

        FD_ZERO(&read_fds);
        FD_ZERO(&write_fds);

        int nfds = ares_fds(channel, &read_fds, &write_fds);

        if (nfds == 0){
            break;
        }

        tvp = ares_timeout(channel, NULL, &tv);
        select(nfds, &read_fds, &write_fds, NULL, tvp);
        ares_process(channel, &read_fds, &write_fds);
    }
}

int dns_lookup(const char * domain) {
    int ret = ares_library_init(ARES_LIB_INIT_ALL);

    if (ret != ARES_SUCCESS){
        fprintf(stderr, "%s\n", ares_strerror(ret));
        return ret;
    }

    struct ares_options options;
    //options.sock_state_cb_data;
    options.sock_state_cb = state_cb;

    int optmask = 0;

    optmask |= ARES_OPT_SOCK_STATE_CB;

    ares_channel_t * channel = NULL;

    ret = ares_init_options(&channel, &options, optmask);

    if (ret != ARES_SUCCESS) {
        fprintf(stderr, "%s\n", ares_strerror(ret));
        return ret;
    }

    ret = ares_set_servers_ports_csv(channel, "8.8.8.8");

    if (ret != ARES_SUCCESS) {
        fprintf(stderr, "%s\n", ares_strerror(ret));
        return ret;
    }

    ares_gethostbyname(channel, domain, AF_INET, callback, NULL);
    //ares_gethostbyname(channel, "google.com", AF_INET6, callback, NULL);
    wait_ares(channel);

    ares_destroy(channel);

    ares_library_cleanup();

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <domain>", argv[0]);
        return 1;
    }

    return dns_lookup(argv[1]);
}
