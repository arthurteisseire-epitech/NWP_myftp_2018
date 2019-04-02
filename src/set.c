/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** set.c
*/

#include <stdlib.h>
#include "myftp.h"

set_t *set_init(void)
{
    set_t *set = calloc(1, sizeof(set_t));

    if (set == NULL)
        exit_with("failed to allocate memory for set");
    return set;
}

void set_add_fd(set_t *set, event_t fd)
{
    set->readfds = realloc(set->readfds, sizeof(fd) * (set->size + 1));
    if (set->readfds == NULL)
        exit_with("failed to realloc readfds");
    set->readfds[set->size] = fd;
    ++set->size;
}

void set_reload_fd_set(set_t *set, fd_set *fd_s)
{
    FD_ZERO(fd_s);
    for (size_t i = 0; i < set->size; ++i)
        if (set->readfds[i].type != FREE)
            FD_SET(set->readfds[i].fd, fd_s);
}

int set_find_max_fd(set_t *set)
{
    int max = 0;

    for (size_t i = 0; i < set->size; ++i)
        if (set->readfds[i].fd > max)
            max = set->readfds[i].fd;
    return (max);
}
