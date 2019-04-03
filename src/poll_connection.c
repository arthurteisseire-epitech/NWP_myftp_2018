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
    connection_t *current = poll->conn;

    while (current != NULL) {
        if (FD_ISSET(current->sock.fd, set))
            current->is_event = true;
        current = current->next;
    }
}

connection_t *poll_connection(poll_t *poll)
{
    connection_t *current = poll->conn;

    while (current != NULL) {
        if (current->is_event) {
            current->is_event = false;
            return (current);
        }
        current = current->next;
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
