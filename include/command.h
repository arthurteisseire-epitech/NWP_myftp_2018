/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** commands.h
*/

#ifndef PSU_MYFTP_2018_COMMAND_H
#define PSU_MYFTP_2018_COMMAND_H

#include "poll.h"

#define COMMAND_NOT_FOUND -12

struct command_s {
    const char *name;
    int (*f)(poll_t *poll, connection_t *conn, const char *input);
};

void exec_command(poll_t *poll, connection_t *conn);
int command_quit(poll_t *poll, connection_t *conn, const char *input);
int command_user(poll_t *poll, connection_t *conn, const char *input);
int command_pass(poll_t *poll, connection_t *conn, const char *input);
int command_pwd(poll_t *poll, connection_t *conn, const char *input);
int command_cwd(poll_t *poll, connection_t *conn, const char *input);
int command_cdup(poll_t *poll, connection_t *conn, const char *input);
int command_list(poll_t *poll, connection_t *conn, const char *input);
int command_noop(poll_t *poll, connection_t *conn, const char *input);
int command_help(poll_t *poll, connection_t *conn, const char *input);
int command_pasv(poll_t *poll, connection_t *conn, const char *input);
int command_retr(poll_t *poll, connection_t *conn, const char *input);
int command_dele(poll_t *poll, connection_t *conn, const char *input);
int command_stor(poll_t *poll, connection_t *conn, const char *input);

static const struct command_s guest_commands[] = {
    {"QUIT", command_quit},
    {"USER", command_user},
    {"PASS", command_pass},
    {NULL, NULL},
};

static const struct command_s admin_commands[] = {
    {"PWD", command_pwd},
    {"CWD", command_cwd},
    {"CDUP", command_cdup},
    {"LIST", command_list},
    {"NOOP", command_noop},
    {"HELP", command_help},
    {"PASV", command_pasv},
    {"RETR", command_retr},
    {"DELE", command_dele},
    {"STOR", command_stor},
    {NULL, NULL},
};

#endif
