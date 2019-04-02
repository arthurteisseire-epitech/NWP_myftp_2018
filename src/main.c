/*
** EPITECH PROJECT, 2018
** PSU_myftp_2018
** File description:
** main.c
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include "myftp.h"
#include "socket.h"

long int get_port(const char *port_str)
{
    long port;
    char *endptr = (char *) port_str;

    port = strtol(port_str, &endptr, 10);
    if (port_str == endptr || port < 1 || port > 65535)
        exit_with("error: '%s' isn't a number between 1 and 65535", port_str);
    return port;
}

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
    fd_set fd_s;
    event_t *event;

    poll_reload_set(poll, &fd_s);
    select(poll_find_max_fd(poll) + 1, &fd_s, NULL, NULL, NULL);
    poll_set_events(poll, &fd_s);
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

int main(int ac, char *av[])
{
    if (ac != 2)
        return (84);
    start_ftp(get_port(av[1]));
    return (0);
}
