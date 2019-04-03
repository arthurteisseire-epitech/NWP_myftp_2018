/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** poll.c
*/

#include <stdlib.h>
#include "poll.h"
#include "utils.h"

poll_t *poll_init(const char *path)
{
    poll_t *poll = safe_malloc(sizeof(poll_t));

    poll->path = path;
    poll->size = 0;
    poll->conn = NULL;
    return poll;
}

void poll_reload_set(poll_t *poll, fd_set *set)
{
    connection_t *current = poll->conn;

    FD_ZERO(set);
    while (current != NULL) {
        if (current->type != FREE)
            FD_SET(current->sock.fd, set);
        current = current->next;
    }
}

int poll_find_max_fd(poll_t *poll)
{
    int max = 0;
    connection_t *current = poll->conn;

    while (current != NULL) {
        if (current->sock.fd > max)
            max = current->sock.fd;
        current = current->next;
    }
    return (max);
}
