/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** set_event.c
*/

#include <stdlib.h>
#include "myftp.h"

void set_set_events(set_t *set, fd_set *fd_s)
{
    for (size_t i = 0; i < set->size; ++i)
        if (FD_ISSET(set->readfds[i].fd, fd_s))
            set->readfds[i].is_event = true;
}

event_t *set_poll_event(set_t *set)
{
    for (size_t i = 0; i < set->size; ++i)
        if (set->readfds[i].is_event) {
            set->readfds[i].is_event = false;
            return (&set->readfds[i]);
        }
    return (NULL);
}
