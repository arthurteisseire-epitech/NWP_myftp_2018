/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** command_pwd.c
*/

#include <stdio.h>
#include <string.h>
#include "poll.h"

int command_pwd(__attribute((unused))poll_t *poll, connection_t *conn,
    __attribute((unused))const char *input)
{
    char path[1024];

    sprintf(path, "%s", conn->user.path);
    if (strcmp(path, "/") != 0)
        path[strlen(path) - 1] = '\0';
    dprintf(conn->sock.fd, "257 \"%s\"\r\n", path);
    return (0);
}
