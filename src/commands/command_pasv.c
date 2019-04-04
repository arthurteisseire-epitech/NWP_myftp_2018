/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** command_pasv.c
*/

#include <arpa/inet.h>
#include <string.h>
#include "code.h"
#include "poll.h"

void replace(char *str, char old, char new)
{
    for (int i = 0; str[i]; ++i)
        if (str[i] == old)
            str[i] = new;
}

void send_ok_message(const connection_t *conn, sock_t *data_sock)
{
    char *ip = strdup(inet_ntoa(data_sock->info.sin_addr));
    char buffer[1024];

    replace(ip, '.', ',');
    sprintf(buffer, "(%s,%d,%d).", ip,
        ntohs(data_sock->info.sin_port) / 256,
        ntohs(data_sock->info.sin_port) % 256);
    send_message(conn->sock.fd, CODE_PASSIVE_MODE, buffer);
    free(ip);
}

int command_pasv(__attribute((unused))poll_t *poll, connection_t *conn,
    __attribute((unused))const char *input)
{
    conn->data_sock = create_socket_with_free_port(&conn->sock.info);
    conn->mode = PASSIVE;
    send_ok_message(conn, &conn->data_sock);
    return (0);
}
