/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** socket.c
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "socket.h"

sock_t create_socket(int port)
{
    sock_t sock;

    sock.size_info = sizeof(sock.info);
    sock.info.sin_family = AF_INET;
    sock.info.sin_port = htons(port);
    sock.info.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    sock.fd = socket(AF_INET, SOCK_STREAM, 0);
    bind(sock.fd, (struct sockaddr *) &sock.info, sock.size_info);
    return sock;
}
