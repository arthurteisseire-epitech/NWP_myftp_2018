/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** command_cwd.c
*/

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "command.h"
#include "code.h"
#include "utils.h"
#include "poll.h"

int command_cwd(poll_t *poll, connection_t *conn, const char *input)
{
    char *second_arg = find_second_arg(input);
    char *tmp = concat(conn->user.path, second_arg);
    char *path = my_realpath(tmp);

    if (path != NULL && strlen(path) >= strlen(poll->path) && is_dir(path)) {
        free(conn->user.path);
        conn->user.path = path;
        send_message(conn->sock.fd, CODE_SUCCESS, "to change directory.");
    } else {
        send_message(conn->sock.fd, CODE_FAILED, "to change directory.");
        free(path);
    }
    free(tmp);
    free(second_arg);
    return (0);
}
