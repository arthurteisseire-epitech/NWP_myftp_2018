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
    char *real_path = concat(poll->path, conn->user.path);
    char *tmp = real_path;
    char *second_arg = find_second_arg(input);

    real_path = concat(real_path, second_arg);
    free(tmp);
    free(second_arg);
    if (conn->mode == NONE)
        return (0);
    if (conn->mode == PASSIVE)
        send_passive(conn, real_path);
    free(real_path);
    return (0);
}
