/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** conn.c
*/

#include "utils.h"
#include "poll.h"

connection_t *create_connection(sock_t *sock, enum fd_type type)
{
    connection_t *conn = safe_malloc(sizeof(connection_t));

    conn->sock = *sock;
    conn->type = type;
    conn->is_event = false;
    return (conn);
}
