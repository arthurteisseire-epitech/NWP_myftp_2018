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

void handle_client_event(poll_t *poll, const event_t *event)
{
    char buffer[1024] = {0};
    int rd_bytes = read(event->sock.fd, buffer, sizeof(buffer));

    if (strncasecmp(buffer, "QUIT", 4) == 0) {
        dprintf(event->sock.fd, "quit !\n");
//        poll_remove_event(poll, event);
    }
}

void handle_event(poll_t *poll, const event_t *event, int sockfd)
{
    sock_t sock;

    if (event->type == SERVER) {
        sock = accept_connection(sockfd);
        poll_add_event(poll, create_event(&sock, CLIENT));
    } else if (event->type == CLIENT) {
        handle_client_event(poll, event);
    }
}

void handle_events(poll_t *poll, sock_t *sock)
{
    fd_set set;
    const event_t *event;

    poll_reload_set(poll, &set);
    select(poll_find_max_fd(poll) + 1, &set, NULL, NULL, NULL);
    poll_set_events(poll, &set);
    while ((event = poll_event(poll)) != NULL)
        handle_event(poll, event, sock->fd);
}

void start_ftp(int port)
{
    poll_t *poll = poll_init();
    sock_t sock = create_socket(port);

    bind_socket(&sock);
    printf("%s\n", inet_ntoa(sock.info.sin_addr));
    poll_add_event(poll, create_event(&sock, SERVER));
    while (1)
        handle_events(poll, &sock);
    close(sock.fd);
}
