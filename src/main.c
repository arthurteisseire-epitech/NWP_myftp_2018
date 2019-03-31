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
    return connfd;
}

int main(int ac, char *av[])
{
    sock_t sock;
    int connfd;
    char buffer[1024];
    int rd_bytes;

    if (ac != 2)
        return (84);
    sock = create_socket(get_port(av[1]));
    bind_socket(&sock);
    printf("%s\n", inet_ntoa(sock.info.sin_addr));
    listen(sock.fd, 5);
    while (1) {
        connfd = wait_connection(sock.fd);
        rd_bytes = read(connfd, buffer, 1024);
        write(connfd, buffer, rd_bytes);
        close(connfd);
    }
    return (0);
}
