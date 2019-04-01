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
    dprintf(connfd, "ip : %s, port: %d\n", inet_ntoa(client.sin_addr), htons(client.sin_port));
    return (connfd);
}

void start_ftp(int port)
{
    set_t *set = set_init();
    sock_t sock;
    fd_set fd_s;
    int connfd = 987;
    int rd_bytes;
    char buffer[1024];

    sock = create_socket(port);
    bind_socket(&sock);
    printf("%s\n", inet_ntoa(sock.info.sin_addr));
    listen(sock.fd, 5);

    set_add_fd(set, (fd_t){sock.fd, SERVER});
    for (int i = 0; i < 3; ++i) {
        set_reload_fd_set(set, &fd_s);
        select(set_find_max_fd(set) + 1, &fd_s, NULL, NULL, NULL);
        if (FD_ISSET((sock).fd, &fd_s)) {
            connfd = wait_connection((sock).fd);
            set_add_fd(set, (fd_t) {connfd, CLIENT});
        } else if (FD_ISSET(connfd, &fd_s)) {
            printf("%d\n", FD_ISSET(connfd, &fd_s));
            rd_bytes = read(connfd, buffer, 1024);
            write(connfd, buffer, rd_bytes);
        }
    }
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
