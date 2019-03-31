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
    char *endptr = (char *)port_str;

    port = strtol(port_str, &endptr, 10);
    if (port_str == endptr || port < 1 || port > 65535)
        exit_with("error: '%s' isn't a number between 1 and 65535", port_str);
    return port;
}

int wait_connection(int fd)
{
    int connfd;

    listen(fd, 1);
    connfd = accept(fd, NULL, NULL);
    if (connfd < 0)
        exit_with("error when accepting");
    return connfd;
}

int main(int ac, char *av[])
{
    sock_t sock;
    int connfd;

    if (ac != 2)
        return (84);
    sock = create_socket(get_port(av[1]));
    printf("%s\n", inet_ntoa(sock.info.sin_addr));
    connfd = wait_connection(sock.fd);
    write(connfd, "Hello World!\n", sizeof("Hello World!\n"));
    return (0);
}
