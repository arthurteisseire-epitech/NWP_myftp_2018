/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** command_cwd.c
*/

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "code.h"
#include "utils.h"
#include "poll.h"

void change_dir(const poll_t *poll, connection_t *conn, const char *input)
{
    DIR *dir;
    char *path = get_dir_path_from_input(poll->path, conn->user.path, input);

    dir = opendir(path);
    if (dir) {
        free(conn->user.path);
        conn->user.path = path;
        send_message(conn->sock.fd, CODE_SUCCESS, "to change directory.");
        closedir(dir);
    } else {
        send_message(conn->sock.fd, CODE_FAILED, "to change directory.");
    }
}

int command_cwd(poll_t *poll, connection_t *conn, const char *input)
{
    if (strcmp(conn->user.path, "/") != 0)
        change_dir(poll, conn, input);
    else
        send_message(conn->sock.fd, CODE_SUCCESS, "to change directory.");
    return (0);
}
