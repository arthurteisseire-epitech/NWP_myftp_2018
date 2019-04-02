/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** poll.h
*/

#ifndef PSU_MYFTP_2018_POLL_H
#define PSU_MYFTP_2018_POLL_H

#include <stdbool.h>
#include <stdlib.h>
#include "socket.h"

enum fd_type {
    SERVER,
    CLIENT,
    FREE
};

typedef struct connection_s {
    sock_t sock;
    enum fd_type type;
    bool is_event;
    struct connection_s *next;
} connection_t;

typedef struct poll_s {
    connection_t *conn;
    size_t size;
} poll_t;

poll_t *poll_init(void);
void poll_add_conn(poll_t *poll, connection_t *conn);
void poll_reload_set(poll_t *poll, fd_set *set);
int poll_find_max_fd(poll_t *poll);
void poll_set_conns(poll_t *poll, fd_set *set);
void poll_remove_conn(poll_t *poll, connection_t *conn);
connection_t *poll_connection(poll_t *poll);

connection_t *create_connection(sock_t *sock, enum fd_type type);

#endif
