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

int main(int ac, char *av[])
{
    sock_t sock;
    fd_set set;
    int connfd = 987;
    int rd_bytes;
    char buffer[1024];

    if (ac != 2)
        return (84);
    sock = create_socket(get_port(av[1]));
    bind_socket(&sock);
    printf("%s\n", inet_ntoa(sock.info.sin_addr));
    listen(sock.fd, 5);

    FD_ZERO(&set);
    for (int i = 0; i < 3; ++i) {
        FD_SET(sock.fd, &set);
        select(65536, &set, NULL, NULL, NULL);
        printf("end select\n");
        if (FD_ISSET(sock.fd, &set)) {
            connfd = wait_connection(sock.fd);
            FD_ZERO(&set);
            FD_SET(connfd, &set);
        } else if (FD_ISSET(connfd, &set)) {
            printf("%d\n", FD_ISSET(connfd, &set));
            rd_bytes = read(connfd, buffer, 1024);
            write(connfd, buffer, rd_bytes);
        }
    }
    FD_CLR(sock.fd, &set);
    close(sock.fd);
    return (0);
}
