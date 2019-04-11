/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** command_pwd.c
*/

#include <stdio.h>
#include <string.h>
#include "poll.h"

int command_pwd(poll_t *poll, connection_t *conn,
    __attribute((unused))const char *input)
{
    printf("%s\n", conn->user.path);
    dprintf(conn->sock.fd, "257 \"/%s\"\r\n",
        conn->user.path + strlen(poll->path));
    return (0);
}
