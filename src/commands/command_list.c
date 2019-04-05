/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** command_list.c
*/

#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include "code.h"
#include "utils.h"
#include "poll.h"

static void send_passive(connection_t *conn, char *real_path)
{
    sock_t sock;
    int child_pid = fork();
    char buffer[1024];

    if (child_pid == 0) {
        sock = accept_connection(conn->data_sock.fd);
        dup2(sock.fd, 1);
        dup2(sock.fd, 2);
        close(conn->data_sock.fd);
        sprintf(buffer, "ls -l %s", real_path);
        system(buffer);
        send_message(conn->sock.fd, CODE_TRANSFER_COMPLETE, NULL);
        exit(0);
    }
    if (child_pid > 0)
        send_message(conn->sock.fd, CODE_STATUS_OK, NULL);
    conn->mode = NONE;
}

int command_list(poll_t *poll, connection_t *conn, const char *input)
{
    char *path = get_file_path_from_input(poll->path, conn->user.path, input);

    if (conn->mode == NONE)
        send_message(conn->sock.fd, CODE_NO_MODE, NULL);
    else if (conn->mode == PASSIVE)
        send_passive(conn, path);
    free(path);
    return (0);
}
