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

void handle_events(set_t *set, sock_t *sock, fd_set *fd_s)
{
    int rd_bytes;
    char buffer[1024];
    fd_t *f;
    int connfd;

    set_reload_fd_set(set, fd_s);
    select(set_find_max_fd(set) + 1, fd_s, NULL, NULL, NULL);
    set_set_events(set, fd_s);
    while ((f = set_poll_event(set)) != NULL) {
        if (f->type == SERVER) {
            connfd = wait_connection((*sock).fd);
            set_add_fd(set, (fd_t) {connfd, CLIENT, false});
        } else if (f->type == CLIENT) {
            rd_bytes = read(f->fd, buffer, 1024);
            write(f->fd, buffer, rd_bytes);
        }
    }
}

void start_ftp(int port)
{
    set_t *set = set_init();
    sock_t sock;
    fd_set fd_s;

    sock = create_socket(port);
    printf("%s\n", inet_ntoa(sock.info.sin_addr));
    set_add_fd(set, (fd_t) {sock.fd, SERVER, false});
    for (int i = 0; i < 3; ++i)
        handle_events(set, &sock, &fd_s);
    FD_CLR(sock.fd, &fd_s);
    close(sock.fd);
}

int main(int ac, char *av[])
{
    if (ac != 2)
        return (84);
    start_ftp(get_port(av[1]));
    return (0);
}
