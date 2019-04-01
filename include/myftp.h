/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** myftp.h
*/

#ifndef PSU_MYFTP_2018_MYFTP_H
#define PSU_MYFTP_2018_MYFTP_H

#include <stdarg.h>

enum fd_type {
    SERVER,
    CLIENT,
    FREE
};

typedef struct fd_s {
    int fd;
    enum fd_type type;
} fd_t;

typedef struct set_s {
    fd_t *readfds;
} set_t;

set_t *set_init(void);
void exit_with(const char *msg, ...);

#endif
