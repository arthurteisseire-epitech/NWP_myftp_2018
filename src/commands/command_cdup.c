/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** command_cdup.c
*/

#include <string.h>
#include "code.h"
#include "poll.h"

static void cdup_dir(connection_t *conn)
{
    conn->user.path[rindex(conn->user.path, '/') - conn->user.path] = '\0';
    conn->user.path[rindex(conn->user.path, '/') - conn->user.path + 1] = '\0';
}

int command_cdup(__attribute((unused))poll_t *poll, connection_t *conn,
    __attribute((unused))const char *input)
{
    if (strcmp(conn->user.path, "/") != 0)
        cdup_dir(conn);
    send_message(conn->sock.fd, CODE_SUCCESS, "to change directory.");
    return (0);
}
