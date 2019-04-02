/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** poll.c
*/

#include <stdlib.h>
#include "poll.h"
#include "utils.h"

poll_t *poll_init(void)
{
    poll_t *poll = calloc(1, sizeof(poll_t));

    if (poll == NULL)
        exit_with("failed to allocate memory for poll");
    return poll;
}

void poll_reload_set(poll_t *poll, fd_set *set)
{
    FD_ZERO(set);
    for (size_t i = 0; i < poll->size; ++i)
        if (poll->conn[i].type != FREE)
            FD_SET(poll->conn[i].sock.fd, set);
}

int poll_find_max_fd(poll_t *poll)
{
    int max = 0;

    for (size_t i = 0; i < poll->size; ++i)
        if (poll->conn[i].sock.fd > max)
            max = poll->conn[i].sock.fd;
    return (max);
}
