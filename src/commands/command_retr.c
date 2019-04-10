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

static void write_all(sock_t *sock, int fd)
{
    char buffer[4096];
    int rd_bytes;

    do {
        rd_bytes = read(fd, buffer, 4096);
        buffer[rd_bytes] = '\0';
        write(sock->fd, buffer, rd_bytes);
    } while (rd_bytes == 4096);
}

static void send_passive(connection_t *conn, const char *path_input)
{
    sock_t sock;
    int fd;
    int child_pid = fork();

    if (child_pid == 0) {
        accept_connection(&conn->data_sock);
        fd = open(path_input, O_RDONLY);
        if (fd < 0) {
            send_message(conn->sock.fd, CODE_FAILED, "to open file.");
            exit(84);
        }
        write_all(&sock, fd);
        send_message(conn->sock.fd, CODE_TRANSFER_COMPLETE, NULL);
        exit(0);
    }
    if (child_pid > 0)
        send_message(conn->sock.fd, CODE_STATUS_OK, NULL);
    conn->mode = NONE;
}

int command_retr(poll_t *poll, connection_t *conn, const char *input)
{
    char *path = get_file_path_from_input(poll->path, conn->user.path, input);

    if (conn->mode == NONE)
        send_message(conn->sock.fd, CODE_NO_MODE, NULL);
    if (conn->mode == PASSIVE)
        send_passive(conn, path);
    conn->mode = NONE;
    free(path);
    return (0);
}
