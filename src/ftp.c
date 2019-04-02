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
#include "myftp.h"
#include "poll.h"
#include "socket.h"

sock_t create_connection(int fd)
{
    sock_t sock;

    sock.size_info = sizeof(struct sockaddr_in);
    sock.fd = accept(fd, (struct sockaddr *) &sock.info, &sock.size_info);
    if (sock.fd < 0)
        exit_with("error when accepting");
    dprintf(sock.fd, "ip : %s, port: %d\n", inet_ntoa(sock.info.sin_addr),
            htons(sock.info.sin_port));
    return (sock);
}

void handle_event(poll_t *poll, int sockfd, const event_t *event)
{
    int rd_bytes;
    char buffer[1024];
    sock_t sock;

    if (event->type == SERVER) {
        sock = create_connection(sockfd);
        poll_add_event(poll, create_event(&sock, CLIENT));
    } else if (event->type == CLIENT) {
        rd_bytes = read(event->sock.fd, buffer, 1024);
        write(event->sock.fd, buffer, rd_bytes);
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
        handle_event(poll, sock->fd, event);
}

void start_ftp(int port)
{
    poll_t *poll = poll_init();
    sock_t sock = create_socket(port);

    printf("%s\n", inet_ntoa(sock.info.sin_addr));
    poll_add_event(poll, create_event(&sock, SERVER));
    for (int i = 0; i < 3; ++i)
        handle_events(poll, &sock);
    close(sock.fd);
}
