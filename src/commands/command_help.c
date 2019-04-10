/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** command_help.c
*/

#include <stdio.h>
#include "command.h"
#include "code.h"
#include "poll.h"

int command_help(__attribute((unused))poll_t *poll, connection_t *conn,
    __attribute((unused))const char *input)
{
    char *space = "";

    for (int i = 0; guest_commands[i].name; ++i)
        dprintf(conn->sock.fd, "%s ", guest_commands[i].name);
    for (int i = 0; admin_commands[i].name; ++i) {
        dprintf(conn->sock.fd, "%s%s", space, admin_commands[i].name);
        space = " ";
    }
    dprintf(conn->sock.fd, "\n");
    send_message(conn->sock.fd, CODE_HELP_OK, NULL);
    return (0);
}
