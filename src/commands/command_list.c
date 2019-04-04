/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** command_list.c
*/

#include <dirent.h>
#include <stdio.h>
#include "utils.h"
#include "poll.h"

void list_dir(const char *realpath, int fd)
{
    DIR *d = opendir(realpath);
    struct dirent *dir;

    if (d) {
        dir = readdir(d);
        while (dir) {
            dprintf(fd, "%s\n", dir->d_name);
            dir = readdir(d);
        }
        closedir(d);
    }
}

int command_list(poll_t *poll, connection_t *conn, const char *input)
{
    char *realpath = concat(poll->path, conn->user.path);
    char *tmp = realpath;
    char *second_arg = find_second_arg(input);

    realpath = concat(realpath, second_arg);
    free(tmp);
    free(second_arg);
    list_dir(realpath, conn->sock.fd);
    free(realpath);
    return (0);
}