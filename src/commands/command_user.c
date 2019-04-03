/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** command_user.c
*/

#include <string.h>
#include <stdio.h>
#include "code.h"
#include "myftp.h"
#include "command.h"

int command_user(__attribute((unused))poll_t *poll,
    connection_t *conn, const char *input)
{
    char *p = (char *)input + 4;

    p += strspn(p, " \r\n");
    if (conn->user.name && strcmp(conn->user.name, USERNAME) == 0)
        return (0);
    free(conn->user.name);
    conn->user.name = strndup(p, strcspn(p, " \r\n"));
    send_message(conn->sock.fd, CODE_USER);
    return (0);
}
