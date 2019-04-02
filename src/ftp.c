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
#include "myftp.h"
#include "socket.h"

int wait_connection(int fd)
{
    int connfd;
    struct sockaddr_in client;
    socklen_t len = sizeof(client);

    connfd = accept(fd, (struct sockaddr *) &client, &len);
    if (connfd < 0)
        exit_with("error when accepting");
    dprintf(connfd, "ip : %s, port: %d\n", inet_ntoa(client.sin_addr),
            htons(client.sin_port));
    return (connfd);
}

void handle_events(poll_t *poll, sock_t *sock)
{
    int rd_bytes;
    char buffer[1024];
    int connfd;
    fd_set set;
    event_t *event;

    poll_reload_set(poll, &set);
    select(poll_find_max_fd(poll) + 1, &set, NULL, NULL, NULL);
    poll_set_events(poll, &set);
    while ((event = poll_event(poll)) != NULL) {
        if (event->type == SERVER) {
            connfd = wait_connection((*sock).fd);
            poll_add_fd(poll, (event_t) {connfd, CLIENT, false});
        } else if (event->type == CLIENT) {
            rd_bytes = read(event->fd, buffer, 1024);
            write(event->fd, buffer, rd_bytes);
        }
    }
}

void start_ftp(int port)
{
    poll_t *poll = poll_init();
    sock_t sock;

    sock = create_socket(port);
    printf("%s\n", inet_ntoa(sock.info.sin_addr));
    poll_add_fd(poll, (event_t) {sock.fd, SERVER, false});
    for (int i = 0; i < 3; ++i)
        handle_events(poll, &sock);
    close(sock.fd);
}
