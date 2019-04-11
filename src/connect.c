/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** connect.c
*/

#include <errno.h>
#include <string.h>
#include "utils.h"
#include "socket.h"

void accept_connection(sock_t *sock)
{
    sock->size_info = sizeof(sock->info);
    sock->fd = accept(sock->fd, (struct sockaddr *)&sock->info,
        &sock->size_info);
    if (sock->fd < 0)
        exit_with("accept: %s", strerror(errno));
}

void connect_socket(sock_t *sock)
{
    sock->size_info = sizeof(sock->info);
    if (connect(sock->fd, (struct sockaddr *)&sock->info,
        sock->size_info) == -1) {
        exit_with("connect: %s", strerror(errno));
    }
}
