/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** command_list.c
*/

#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <libnet.h>
#include "code.h"
#include "utils.h"
#include "poll.h"

static void send_active(connection_t *conn, char *real_path)
{
    int child_pid = fork();
    char buffer[1024];

    if (child_pid == 0) {
        if (connect(conn->data_sock.fd, (struct sockaddr *) &conn->data_sock.info,
            conn->data_sock.size_info) == -1) {
            perror("connect");
            return;
        }
        dup2(conn->data_sock.fd, 1);
        dup2(conn->data_sock.fd, 2);
        sprintf(buffer, "ls -l %s", real_path);
        system(buffer);
        send_message(conn->sock.fd, CODE_TRANSFER_COMPLETE, NULL);
        exit(0);
    }
    if (child_pid > 0)
        send_message(conn->sock.fd, CODE_STATUS_OK, NULL);
}

static void send_passive(connection_t *conn, char *real_path)
{
    int child_pid = fork();
    char buffer[1024];

    if (child_pid == 0) {
        accept_connection(&conn->data_sock);
        dup2(conn->data_sock.fd, 1);
        dup2(conn->data_sock.fd, 2);
        sprintf(buffer, "ls -l %s", real_path);
        system(buffer);
        send_message(conn->sock.fd, CODE_TRANSFER_COMPLETE, NULL);
        exit(0);
    }
    if (child_pid > 0)
        send_message(conn->sock.fd, CODE_STATUS_OK, NULL);
}

int command_list(poll_t *poll, connection_t *conn, const char *input)
{
    char *path = get_file_path_from_input(poll->path, conn->user.path, input);

    if (conn->mode == PASSIVE)
        send_passive(conn, path);
    else if (conn->mode == ACTIVE)
        send_active(conn, path);
    else
        send_message(conn->sock.fd, CODE_NO_MODE, NULL);
    conn->mode = NONE;
    free(path);
    return (0);
}
