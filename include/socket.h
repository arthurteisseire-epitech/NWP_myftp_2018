/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** socket.h
*/

#ifndef PSU_MYFTP_2018_SOCKET_H
#define PSU_MYFTP_2018_SOCKET_H

#include <netinet/in.h>

typedef struct sock_s {
    struct sockaddr_in info;
    size_t size_info;
    int fd;
    int port;
} sock_t;

sock_t create_socket(int port);
void bind_socket(sock_t *sock);

#endif
