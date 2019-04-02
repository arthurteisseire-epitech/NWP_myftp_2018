/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** poll.c
*/

#include <stdlib.h>
#include "poll.h"
#include "myftp.h"

poll_t *poll_init(void)
{
    poll_t *poll = calloc(1, sizeof(poll_t));

    if (poll == NULL)
        exit_with("failed to allocate memory for poll");
    return poll;
}

void poll_add_fd(poll_t *poll, event_t fd)
{
    poll->readfds = realloc(poll->readfds, sizeof(fd) * (poll->size + 1));
    if (poll->readfds == NULL)
        exit_with("failed to realloc readfds");
    poll->readfds[poll->size] = fd;
    ++poll->size;
}

void poll_reload_set(poll_t *poll, fd_set *set)
{
    FD_ZERO(set);
    for (size_t i = 0; i < poll->size; ++i)
        if (poll->readfds[i].type != FREE)
            FD_SET(poll->readfds[i].fd, set);
}

int poll_find_max_fd(poll_t *poll)
{
    int max = 0;

    for (size_t i = 0; i < poll->size; ++i)
        if (poll->readfds[i].fd > max)
            max = poll->readfds[i].fd;
    return (max);
}
