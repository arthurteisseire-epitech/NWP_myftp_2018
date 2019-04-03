/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** command_quit.c
*/

#include <stdio.h>
#include "command.h"

int command_quit(poll_t *poll, connection_t *conn,
    __attribute((unused))const char *input)
{
    dprintf(conn->sock.fd, "bye\n");
    poll_remove_conn(poll, conn);
    return (0);
}
