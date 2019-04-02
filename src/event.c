/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** event.c
*/

#include "utils.h"
#include "poll.h"

event_t *create_event(sock_t *sock, enum fd_type type)
{
    event_t *event = safe_malloc(sizeof(event_t));

    event->sock = *sock;
    event->type = type;
    event->is_event = false;
    return (event);
}
