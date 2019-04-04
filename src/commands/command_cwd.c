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

static char *get_path(const connection_t *conn, const char *input_path)
{
    char *path = safe_malloc(strlen(conn->user.path) + strlen(input_path) + 2);

    strcpy(path, conn->user.path);
    strcat(path, input_path);
    strcat(path, "/");
    return (path);
}

int command_cwd(poll_t *poll, connection_t *conn, const char *input)
{
    DIR *dir;
    char *input_path = find_second_arg(input);
    char *real_path;
    char *path;

    path = get_path(conn, input_path);
    real_path = concat(poll->path, path);
    dir = opendir(real_path);
    if (dir) {
        free(conn->user.path);
        conn->user.path = path;
        send_message(conn->sock.fd, CODE_SUCCESS_CHANGE_DIR);
        closedir(dir);
    } else {
        send_message(conn->sock.fd, CODE_FAILED_CHANGE_DIR);
    }
    free(real_path);
    free(input_path);
    return (0);
}
