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

void change_dir(const poll_t *poll, connection_t *conn, const char *input,
    const char *second_arg)
{
    DIR *dir;
    char *path;

    if (second_arg[0] == '/')
        path = get_dir_path_from_input(poll->path, "", input);
    else
        path = get_dir_path_from_input(poll->path, conn->user.path, input);
    dir = opendir(path);
    if (dir) {
        free(conn->user.path);
        conn->user.path = get_user_path(path);
        send_message(conn->sock.fd, CODE_SUCCESS, "to change directory.");
        closedir(dir);
    } else {
        send_message(conn->sock.fd, CODE_FAILED, "to change directory.");
    }
    free(path);
}

int command_cwd(poll_t *poll, connection_t *conn, const char *input)
{
    char *second_arg = find_second_arg(input);

    if (strcmp(second_arg, "..") == 0)
        command_cdup(poll, conn, input);
    else
        change_dir(poll, conn, input, second_arg);
    free(second_arg);
    return (0);
}
