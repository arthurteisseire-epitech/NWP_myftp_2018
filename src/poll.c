/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** poll.c
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "poll.h"
#include "utils.h"

static int last_index(const char *s)
{
    size_t len = strlen(s);

    return (len == 0 ? 0 : len - 1);
}

poll_t *poll_init(char *path)
{
    poll_t *poll = safe_malloc(sizeof(poll_t));

    if (strcmp(path, "/") != 0 && path[last_index(path)] == '/')
        path[last_index(path)] = '\0';
    poll->path = my_realpath(path);
    poll->size = 0;
    poll->conn = NULL;
    return (poll);
}

void poll_reload_set(poll_t *poll, fd_set *set)
{
    connection_t *current = poll->conn;

    FD_ZERO(set);
    while (current != NULL) {
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
