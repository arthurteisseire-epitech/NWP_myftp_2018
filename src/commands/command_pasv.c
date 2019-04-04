/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** command_pasv.c
*/

#include "code.h"
#include "poll.h"

int command_pasv(__attribute((unused))poll_t *poll, connection_t *conn,
    __attribute((unused))const char *input)
{
    sock_t data_sock = create_socket_with_free_port();

    data_sock.info = conn->sock.info;
    data_sock.size_info = conn->sock.size_info;
    conn->mode = PASSIVE;
    send_message(conn->sock.fd, CODE_PASSIVE_MODE);
    return (0);
}
