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

static void send_mode(connection_t *conn, const char *path,
    void (*f)(sock_t *))
{
    int fd;
    int child_pid = fork();

    if (child_pid == 0) {
        f(&conn->data_sock);
        fd = open(path, O_RDONLY);
        if (fd < 0 || is_dir(path)) {
            send_message(conn->sock.fd, CODE_FAILED, "to open file.");
            exit(84);
        }
        write_all(&conn->data_sock, fd);
        send_message(conn->sock.fd, CODE_TRANSFER_COMPLETE, NULL);
        exit(0);
    }
    send_message(conn->sock.fd, CODE_STATUS_OK, NULL);
    close(conn->data_sock.fd);
}

int command_retr(__attribute((unused))poll_t *poll, connection_t *conn,
    const char *input)
{
    char *path = get_file_path_from_input(conn->user.path, input);

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
