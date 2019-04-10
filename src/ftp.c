/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** ftp.c
*/

#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <poll.h>
#include <stdbool.h>
#include <string.h>
#include <netdb.h>
#include "myftp.h"
#include "poll.h"
#include "socket.h"
#include "command.h"
#include "code.h"

void handle_connection(poll_t *poll, connection_t *conn, int sockfd)
{
    sock_t sock;

    if (conn->type == SERVER) {
        sock = accept_connection(sockfd);
        poll_add_conn(poll, create_connection(&sock, CLIENT));
        send_message(sock.fd, CODE_CONNECTION, NULL);
    } else if (conn->type == CLIENT) {
        exec_command(poll, conn);
    }
}

void handle_connections(poll_t *poll, sock_t *sock)
{
    fd_set set;
    connection_t *conn;

    poll_reload_set(poll, &set);
    select(poll_find_max_fd(poll) + 1, &set, NULL, NULL, NULL);
    poll_set_conns(poll, &set);
    while ((conn = poll_connection(poll)) != NULL)
        handle_connection(poll, conn, sock->fd);
}

void start_ftp(int port, char *path)
{
    poll_t *poll = poll_init(path);
    sock_t sock = create_socket(port);

    bind_socket(&sock);
    poll_add_conn(poll, create_connection(&sock, SERVER));
    while (1)
        handle_connections(poll, &sock);
}
