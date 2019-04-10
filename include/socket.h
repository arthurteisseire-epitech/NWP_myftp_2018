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
    socklen_t size_info;
    int fd;
} sock_t;

sock_t init_socket(int fd, int port);
sock_t create_socket(int port);
void accept_connection(sock_t *sock);
void bind_socket(sock_t *sock);
sock_t create_socket_with_free_port(struct sockaddr_in *addr);

#endif
