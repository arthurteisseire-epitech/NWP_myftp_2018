/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** command_retr.c
*/

#include <fcntl.h>
#include <unistd.h>
#include "code.h"
#include "poll.h"
#include "utils.h"

static void send_passive(connection_t *conn, const char *path_input)
{
    char buffer[4096];
    int rd_bytes;
    sock_t sock;
    int fd;
    int child_pid = fork();

    if (child_pid == 0) {
        sock = accept_connection(conn->data_sock.fd);
        fd = open(path_input, O_RDONLY);
        if (fd < 0)
            exit(84);
        rd_bytes = read(fd, buffer, 4096);
        write(sock.fd, buffer, rd_bytes);
        send_message(conn->sock.fd, CODE_TRANSFER_COMPLETE, NULL);
        close(conn->data_sock.fd);
        close(sock.fd);
        exit(0);
    }
    if (child_pid > 0)
        send_message(conn->sock.fd, CODE_STATUS_OK, NULL);
    conn->mode = NONE;
}

int command_retr(poll_t *poll, connection_t *conn,
    const char *input)
{
    char *path_input = find_second_arg(input);
    char *real_path = concat(poll->path, "/");
    char *tmp = real_path;

    real_path = concat(real_path, path_input);
    if (conn->mode == PASSIVE)
        send_passive(conn, real_path);
    conn->mode = NONE;
    free(tmp);
    free(real_path);
    free(path_input);
    return (0);
}
