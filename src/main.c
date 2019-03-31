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
#include "socket.h"

int main(int ac, char *av[])
{
    sock_t sock;
    int connfd;

    if (ac != 2)
        return (84);
    sock = create_socket(atoi(av[1]));
    printf("%s\n", inet_ntoa(sock.info.sin_addr));
    listen(sock.fd, 1);
    connfd = accept(sock.fd, NULL, NULL);
    write(connfd, "Hello World!\n", sizeof("Hello World!\n"));
    return (0);
}