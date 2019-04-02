/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** socket.c
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <stdio.h>
#include "myftp.h"
#include "socket.h"

sock_t init_socket(int fd, int port)
{
    sock_t sock;

    sock.fd = fd;
    sock.port = port;
    sock.size_info = sizeof(sock.info);
    sock.info.sin_family = AF_INET;
    sock.info.sin_port = htons(port);
    sock.info.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    return (sock);
}

sock_t create_socket(int port)
{
    sock_t sock;
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    if (fd < 0)
        exit_with("error when creating socket");
    sock = init_socket(fd, port);
    if (bind(sock.fd, (struct sockaddr *) &sock.info, sock.size_info) < 0)
        exit_with("error on binding socket with port : '%d'", sock.port);
    listen(sock.fd, 5);
    return sock;
}

sock_t accept_connection(int fd)
{
    sock_t sock;

    sock.size_info = sizeof(struct sockaddr_in);
    sock.fd = accept(fd, (struct sockaddr *) &sock.info, &sock.size_info);
    if (sock.fd < 0)
        exit_with("error when accepting");
    dprintf(sock.fd, "ip : %s, port: %d\n", inet_ntoa(sock.info.sin_addr),
            htons(sock.info.sin_port));
    return (sock);
}
