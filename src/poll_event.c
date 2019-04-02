/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** poll_event.c
*/

#include <stdlib.h>
#include "poll.h"
#include "myftp.h"

void poll_set_events(poll_t *poll, fd_set *set)
{
    for (size_t i = 0; i < poll->size; ++i)
        if (FD_ISSET(poll->readfds[i].sock.fd, set))
            poll->readfds[i].is_event = true;
}

const event_t *poll_event(poll_t *poll)
{
    for (size_t i = 0; i < poll->size; ++i)
        if (poll->readfds[i].is_event) {
            poll->readfds[i].is_event = false;
            return (&poll->readfds[i]);
        }
    return (NULL);
}

void poll_add_event(poll_t *poll, event_t *event)
{
    event->next = poll->readfds;
    poll->readfds = event;
    ++poll->size;
}
