/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** command_quit.c
*/

#include <stdio.h>
#include "code.h"
#include "command.h"

int command_quit(poll_t *poll, connection_t *conn,
    __attribute((unused))const char *input)
{
    send_message(conn->sock.fd, CODE_QUIT, NULL);
    poll_remove_conn(poll, conn);
    return (0);
}
