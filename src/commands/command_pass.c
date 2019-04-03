/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** command_pass.c
*/

#include <string.h>
#include <stdio.h>
#include "poll.h"

int command_pass(__attribute((unused))poll_t *poll,
    connection_t *conn, const char *input)
{
    char *p = (char *)input;

    if (strcmp(conn->user.name, "Anonymous") == 0) {
        p += 4;
        p += strspn(p, " \r\n");
        dprintf(conn->sock.fd, "%s\n", p);
        if (*p == 0) {
            dprintf(conn->sock.fd, "connected\n");
        }
    }
    return (0);
}
