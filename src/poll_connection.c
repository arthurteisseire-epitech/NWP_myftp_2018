/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** poll_conn.c
*/

#include <stdlib.h>
#include <unistd.h>
#include "poll.h"
#include "myftp.h"

void poll_set_conns(poll_t *poll, fd_set *set)
{
    for (size_t i = 0; i < poll->size; ++i)
        if (FD_ISSET(poll->conn[i].sock.fd, set))
            poll->conn[i].is_event = true;
}

connection_t * poll_connection(poll_t *poll)
{
    for (size_t i = 0; i < poll->size; ++i)
        if (poll->conn[i].is_event) {
            poll->conn[i].is_event = false;
            return (&poll->conn[i]);
        }
    return (NULL);
}

void poll_add_conn(poll_t *poll, connection_t *conn)
{
    conn->next = poll->conn;
    poll->conn = conn;
    ++poll->size;
}

void poll_remove_conn(poll_t *poll, connection_t *conn)
{
    connection_t **current = &poll->conn;

    while (*current != NULL) {
        if (*current == conn) {
            *current = conn->next;
            close(conn->sock.fd);
            free(conn);
            --poll->size;
        }
        current = &(*current)->next;
    }
}
