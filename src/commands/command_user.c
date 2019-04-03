/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** command_user.c
*/

#include <string.h>
#include <stdio.h>
#include "myftp.h"
#include "command.h"

int command_user(__attribute((unused))poll_t *poll,
    connection_t *conn, const char *input)
{
    char *p = (char *)input + 4;

    p += strspn(p, " ");
    if (strncmp(p, USERNAME, sizeof(USERNAME) - 1) == 0) {
        conn->user.name = USERNAME;
        dprintf(conn->sock.fd, "%d User name okay, need password.\n", 331);
    } else {
        dprintf(conn->sock.fd, "%d Invalid username or password.\n", 430);
    }
    return (0);
}
