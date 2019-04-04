/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** command_noop.c
*/

#include "code.h"
#include "poll.h"

int command_noop(__attribute((unused))poll_t *poll, connection_t *conn,
    __attribute((unused))const char *input)
{
    send_message(conn->sock.fd, CODE_OK, NULL);
    return (0);
}
