/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** myftp.h
*/

#ifndef PSU_MYFTP_2018_MYFTP_H
#define PSU_MYFTP_2018_MYFTP_H

#include <stdarg.h>
#include <stdbool.h>

enum fd_type {
    SERVER,
    CLIENT,
    FREE
};

typedef struct event_s {
    int fd;
    enum fd_type type;
    bool is_event;
} event_t;

typedef struct poll_s {
    event_t *readfds;
    size_t size;
} poll_t;

void start_ftp(int port);

poll_t *poll_init(void);
void poll_add_fd(poll_t *poll, event_t fd);
void poll_reload_set(poll_t *poll, fd_set *set);
int poll_find_max_fd(poll_t *poll);
void poll_set_events(poll_t *poll, fd_set *set);
event_t *poll_event(poll_t *poll);
void exit_with(const char *msg, ...);

#endif
