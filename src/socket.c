/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** socket.c
*/

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <netdb.h>
#include <errno.h>
#include "utils.h"
#include "socket.h"

sock_t init_socket(int fd, int port)
{
    sock_t sock;

    sock.fd = fd;
    sock.size_info = sizeof(sock.info);
    sock.info.sin_family = AF_INET;
    sock.info.sin_port = htons(port);
    sock.info.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    return (sock);
}

sock_t create_socket(int port)
{
    sock_t sock;
    int fd = socket(AF_INET, SOCK_STREAM, getprotobyname("TCP")->p_proto);
    int optval = 1;

    if (fd < 0)
        exit_with("socket: %s", strerror(errno));
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int)) == -1)
        exit_with("setsockopt: %s", strerror(errno));
    sock = init_socket(fd, port);
    return sock;
}

void bind_socket(sock_t *sock)
{
    if (bind(sock->fd, (struct sockaddr *) &sock->info, sock->size_info) == -1)
        exit_with("bind: %s", strerror(errno));
    listen(sock->fd, 5);
}

void accept_connection(sock_t *sock)
{
    sock->size_info = sizeof(struct sockaddr_in);
    sock->fd = accept(sock->fd, (struct sockaddr *) &sock->info, &sock->size_info);
    if (sock->fd < 0)
        exit_with("accept: %s", strerror(errno));
}

sock_t create_socket_with_free_port(struct sockaddr_in *addr)
{
    int port = 2000;
    sock_t sock = create_socket(port);

    sock.info = *addr;
    sock.size_info = sizeof(sock.info);
    while (port < 65536) {
        sock.info.sin_port = htons(port);
        if (bind(sock.fd, (struct sockaddr *) &sock.info,
            sock.size_info) == 0) {
            listen(sock.fd, 1);
            return (sock);
        }
        ++port;
    }
    exit_with("no more ports available on the system");
    return (sock);
}
