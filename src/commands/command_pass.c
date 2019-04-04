/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** command_pass.c
*/

#include <string.h>
#include <stdio.h>
#include "utils.h"
#include "myftp.h"
#include "code.h"
#include "poll.h"

int command_pass(__attribute((unused))poll_t *poll,
    connection_t *conn, const char *input)
{
    char *p = find_second_arg(input);

    if (!conn->user.name) {
        send_message(conn->sock.fd, CODE_LOGIN_FIRST);
        return (0);
    }
    if (strcmp(conn->user.name, USERNAME) == 0) {
        free(conn->user.password);
        conn->user.password = p;
        if (*p == '\0')
            send_message(conn->sock.fd, CODE_LOGIN_SUCCESS);
    } else {
        send_message(conn->sock.fd, CODE_LOGIN_INCORRECT);
    }
    return (0);
}
