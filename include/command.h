/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** commands.h
*/

#ifndef PSU_MYFTP_2018_COMMAND_H
#define PSU_MYFTP_2018_COMMAND_H

#include "poll.h"

#define COMMAND_NOT_FOUND -1

struct command_s {
    const char *name;
    int (*f)(poll_t *poll, connection_t *conn, const char *input);
};

void exec_command(poll_t *poll, connection_t *conn);
int command_quit(poll_t *poll, connection_t *conn, const char *input);
int command_user(poll_t *poll, connection_t *conn, const char *input);
int command_pass(poll_t *poll, connection_t *conn, const char *input);

static const struct command_s guest_commands[] = {
    {"QUIT", command_quit},
    {"USER", command_user},
    {"PASS", command_pass},
    {NULL, NULL},
};

static const struct command_s admin_commands[] = {
    {NULL, NULL},
};

#endif
