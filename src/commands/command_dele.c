/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** commande_dele.c
*/

#include <string.h>
#include <stdio.h>
#include "code.h"
#include "utils.h"
#include "poll.h"

static char *get_path(const connection_t *conn, const char *input_path)
{
    char *path = safe_malloc(strlen(conn->user.path) + strlen(input_path) + 2);

    strcpy(path, conn->user.path);
    strcat(path, input_path);
    return (path);
}

int command_dele(poll_t *poll, connection_t *conn, const char *input)
{
    char *input_path = find_second_arg(input);
    char *path = get_path(conn, input_path);
    char *real_path = concat(poll->path, path);

    if (remove(real_path) == -1)
        send_message(conn->sock.fd, CODE_FAILED, "to remove");
    else
        send_message(conn->sock.fd, CODE_SUCCESS, "to remove");
    return (0);
}
