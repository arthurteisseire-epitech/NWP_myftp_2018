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
#include "myftp.h"
#include "poll.h"
#include "socket.h"

void handle_client_event(const event_t *event)
{
    char buffer[1024] = {0};
    int rd_bytes = read(event->sock.fd, buffer, sizeof(buffer));

    dprintf(event->sock.fd, "%d\n", rd_bytes);
    if (strcasecmp(buffer, "PASV\r\n") == 0) {
        write(event->sock.fd, "PASV\n", 5);
    }
}

void handle_event(poll_t *poll, const event_t *event, int sockfd)
{
    sock_t sock;

    if (event->type == SERVER) {
        sock = accept_connection(sockfd);
        poll_add_event(poll, create_event(&sock, CLIENT));
    } else if (event->type == CLIENT) {
        handle_client_event(event);
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

    printf("%s\n", inet_ntoa(sock.info.sin_addr));
    poll_add_event(poll, create_event(&sock, SERVER));
    for (int i = 0; i < 3; ++i)
        handle_events(poll, &sock);
    close(sock.fd);
}
