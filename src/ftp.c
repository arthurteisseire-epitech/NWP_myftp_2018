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

//static sock_t create_socket_with_free_port(void)
//{
//    int port = 2000;
//    sock_t sock = create_socket(0);
//
//    while (port < 65535) {
//        sock.fd = port;
//        if (bind(sock.fd, (struct sockaddr *) &sock.info, sock.size_info) >= 0)
//            return (sock);
//        ++port;
//    }
//    exit_with("no more ports available on the system");
//    return (sock);
//}

bool startsWith(const char *pre, const char *str)
{
    size_t len_pre = strlen(pre);
    size_t len_str = strlen(str);

    return len_str < len_pre ? false : strncasecmp(pre, str, len_pre) == 0;
}

void handle_client_connection(poll_t *poll, connection_t *conn)
{
    char input[64] = {0};
    int rd_bytes = read(conn->sock.fd, input, sizeof(input));

    input[rd_bytes] = '\0';
    for (int i = 0; commands[i].name; ++i)
        if (startsWith(commands[i].name, input))
            commands[i].f(poll, conn, input);
}

void handle_connection(poll_t *poll, connection_t *conn, int sockfd)
{
    sock_t sock;

    if (conn->type == SERVER) {
        sock = accept_connection(sockfd);
        poll_add_conn(poll, create_connection(&sock, CLIENT));
    } else if (conn->type == CLIENT) {
        handle_client_connection(poll, conn);
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

void start_ftp(int port)
{
    poll_t *poll = poll_init();
    sock_t sock = create_socket(port);

    bind_socket(&sock);
    printf("%s\n", inet_ntoa(sock.info.sin_addr));
    poll_add_conn(poll, create_connection(&sock, SERVER));
    while (1)
        handle_connections(poll, &sock);
    close(sock.fd);
}
