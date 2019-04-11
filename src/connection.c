/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** conn.c
*/

#include <string.h>
#include <stdio.h>
#include "utils.h"
#include "poll.h"

static struct user_s init_user(const char *path)
{
    struct user_s user;

    user.password = NULL;
    user.name = NULL;
    user.path = my_realpath(path);
    user.is_logged = false;
    return (user);
}

connection_t *create_connection(sock_t *sock, enum fd_type type,
    const char *path)
{
    connection_t *conn = safe_malloc(sizeof(connection_t));

    conn->user = init_user(path);
    conn->sock = *sock;
    conn->type = type;
    conn->mode = NONE;
    conn->is_event = false;
    conn->next = NULL;
    return (conn);
}

void delete_connection(connection_t *conn)
{
    free(conn->user.name);
    free(conn->user.password);
    free(conn->user.path);
    free(conn);
}
