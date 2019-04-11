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

static void send_mode(connection_t *conn, char *path, void (*f)(sock_t *))
{
    int child_pid = fork();
    char buffer[1024];

    if (child_pid == 0) {
        f(&conn->data_sock);
        dup2(conn->data_sock.fd, 1);
        dup2(conn->data_sock.fd, 2);
        sprintf(buffer, "ls -l %s", path);
        system(buffer);
        send_message(conn->sock.fd, CODE_TRANSFER_COMPLETE, NULL);
        exit(0);
    }
    send_message(conn->sock.fd, CODE_STATUS_OK, NULL);
    close(conn->data_sock.fd);
}

int command_list(poll_t *poll, connection_t *conn, const char *input)
{
    char *path = get_file_path_from_input(poll->path, conn->user.path, input);

    if (conn->mode == PASSIVE)
        send_mode(conn, path, accept_connection);
    else if (conn->mode == ACTIVE)
        send_mode(conn, path, connect_socket);
    else
        send_message(conn->sock.fd, CODE_NO_MODE, NULL);
    conn->mode = NONE;
    free(path);
    return (0);
}
