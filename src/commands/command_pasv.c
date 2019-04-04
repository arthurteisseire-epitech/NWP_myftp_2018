/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** command_pasv.c
*/

#include <arpa/inet.h>
#include "string_ext.h"
#include "code.h"
#include "poll.h"

void send_ok_message(const connection_t *conn, sock_t *data_sock)
{
    char **tok = strsplit(inet_ntoa(data_sock->info.sin_addr), ".");
    char *ip = strjoin((const char **) tok, ", ");
    char buffer[1024];

    sprintf(buffer, "(%s, %d, %d)", ip, data_sock->port / 256,
            data_sock->port % 256);
    send_message(conn->sock.fd, CODE_PASSIVE_MODE, buffer);
    free(tok);
    free(ip);
}

int command_pasv(__attribute((unused))poll_t *poll, connection_t *conn,
                 __attribute((unused))const char *input)
{
    conn->data_sock = create_socket_with_free_port();

    conn->data_sock.info = conn->sock.info;
    conn->data_sock.size_info = conn->sock.size_info;
    conn->mode = PASSIVE;
    send_ok_message(conn, &conn->data_sock);
    return (0);
}
