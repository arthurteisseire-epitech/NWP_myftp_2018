/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** command_stor.c
*/

#include <unistd.h>
#include <fcntl.h>
#include "code.h"
#include "poll.h"
#include "utils.h"

static int write_all(connection_t *conn, int fd, const char *serv_path)
{
    char buffer[4096];
    int rd_bytes;
    int serv_fd = open(serv_path, O_CREAT | O_WRONLY, 0644);

    printf("%s\n", serv_path);
    if (serv_fd < 0) {
        send_message(conn->sock.fd, CODE_FAILED, "to create file.");
        return (84);
    }
    do {
        rd_bytes = read(fd, buffer, 4096);
        write(serv_fd, buffer, rd_bytes);
    } while (rd_bytes == 4096);
    return (0);
}

static void send_file(connection_t *conn, const char *file_path,
    const char *serv_path)
{
    int fd;
    int child_pid = fork();

    if (child_pid == 0) {
        fd = open(file_path, O_RDONLY);
        if (fd < 0) {
            send_message(conn->sock.fd, CODE_FAILED, "to open file.");
            exit(84);
        }
        if (write_all(conn, fd, serv_path) == 0)
            send_message(conn->sock.fd, CODE_TRANSFER_COMPLETE, NULL);
        exit(0);
    }
    if (child_pid > 0)
        send_message(conn->sock.fd, CODE_STATUS_OK, NULL);
    conn->mode = NONE;
}

int command_stor(poll_t *poll, connection_t *conn,
    const char *input)
{
    char *file_path = find_second_arg(input);
    char *serv_path = get_file_path_from_input(poll->path, conn->user.path,
        input);

    if (conn->mode == NONE)
        send_message(conn->sock.fd, CODE_NO_MODE, NULL);
    if (conn->mode == PASSIVE)
        send_file(conn, file_path, serv_path);
    conn->mode = NONE;
    free(file_path);
    return (0);
}
