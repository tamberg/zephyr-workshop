//#include <stdio.h>
//#include <stddef.h>
//#include <unistd.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>
//#include <string.h>

// POSIX_C_LANG_SUPPORT // strlen()
// CONFIG_NET_SOCKETS // zsock_...
// CONFIG_NET_SOCKETS_POSIX_NAMES

#include <zephyr/zephyr.h>
//#include <zephyr/kernel.h>
//#include <zephyr/logging/log.h>
//LOG_MODULE_REGISTER(net_http_client_sample, LOG_LEVEL_DBG);
#include <zephyr/net/socket.h>
#include <zephyr/net/net_ip.h>

int main() {
    // Client
    int sock_fd = zsock_socket(AF_INET, SOCK_STREAM, 0); // create socket

    // Internet Domain Addr
    struct sockaddr_in sv_addr_in;
    sv_addr_in.sin_family = AF_INET;
    sv_addr_in.sin_port = htons(80);
    zsock_inet_pton(AF_INET, "52.218.49.114", &(sv_addr_in.sin_addr));

    zsock_connect(sock_fd, (struct sockaddr *) &sv_addr_in, sizeof(struct sockaddr_in)); // connect socket to sv_addr

    printk("client: writing request...\n");
    char *http_req = "GET /hello.html HTTP/1.1\r\nHost: tmb.gr\r\n\r\n";
    zsock_send(sock_fd, http_req, strlen(http_req), 0);

    printk("client: reading response...\n");
    int n = 1024;
    char buf[n];
    int r = zsock_recv(sock_fd, buf, n, 0);
    buf[r] = '\0';
    printk("%s", buf);

    zsock_close(sock_fd);
    k_sleep(K_FOREVER);
    return 0;
}
