/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** conn.c
*/

#include "utils.h"
#include "poll.h"

static struct user_s init_user(void)
{
    struct user_s user;

    user.password = NULL;
    user.name = NULL;
    return (user);
}

connection_t *create_connection(sock_t *sock, enum fd_type type)
{
    connection_t *conn = safe_malloc(sizeof(connection_t));

    conn->user = init_user();
    conn->sock = *sock;
    conn->type = type;
    conn->is_event = false;
    conn->next = NULL;
    return (conn);
}

void delete_connection(connection_t *conn)
{
    free(conn->user.name);
    free(conn->user.password);
    free(conn);
}
